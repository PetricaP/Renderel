#include "GameEventHandler.hpp"
#include "InputControl.hpp"
#include "WindowGLFW.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/OBJLoader.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <memory>

using namespace renderel;
using namespace math;
using namespace graphics;

#define WIDTH 1080
#define HEIGHT 720

using APIWindow = WindowGLFW;

int main() {
    GameEventHandler gameEventHandler;
    InputControl horizontal;
    InputControl vertical;

    gameEventHandler.AddKeyControl(GLFW_KEY_A, horizontal, -1.0f);
    gameEventHandler.AddKeyControl(GLFW_KEY_D, horizontal, 1.0f);
    gameEventHandler.AddKeyControl(GLFW_KEY_S, vertical, -1.0f);
    gameEventHandler.AddKeyControl(GLFW_KEY_W, vertical, 1.0f);

    gameEventHandler.AddKeyControl(GLFW_KEY_LEFT, horizontal, -1.0f);
    gameEventHandler.AddKeyControl(GLFW_KEY_RIGHT, horizontal, 1.0f);
    gameEventHandler.AddKeyControl(GLFW_KEY_DOWN, vertical, -1.0f);
    gameEventHandler.AddKeyControl(GLFW_KEY_UP, vertical, 1.0f);

    Window *window =
        new APIWindow(WIDTH, HEIGHT, "Renderel", &gameEventHandler);

    Renderer<unsigned int>::InitGraphics();
    Renderer<unsigned int>::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    BasicRenderer<unsigned int> renderer;

	float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, // 2
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, // 1
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // 3
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // 4
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, // 5
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, // 6
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f  // 7
    };

    unsigned int indices[] = {
        // Back face
        0, 1, 2, //
        1, 2, 3, //
        // Front face
        4, 5, 6, //
        5, 6, 7, //
        // Left face
        0, 2, 4, //
        2, 4, 6, //
        // Right face
        1, 3, 5, //
        3, 5, 7, //
        // Top face
        2, 3, 6, //
        3, 6, 7, //
        // Bottom face
        0, 1, 4, //
        1, 4, 5  //
    };

    /* VertexArray *va = new VertexArray();

    VertexBuffer *vb = new VertexBuffer(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(3);
	layout.Push<float>(2);

    va->AddBuffer(vb, layout);

    IndexBuffer<unsigned int> *ib = new IndexBuffer<unsigned int>(
        indices, sizeof(indices) / sizeof(indices[0])); */

    IndexBuffer<unsigned int> *ib = nullptr;
    VertexArray *va = nullptr;

    if (!OBJLoader::Load<>("res/models/munk.obj", ib, va)) {
        std::cerr << "Failed to load OBJ! file" << std::endl;
        return 1;
    }

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

	shader.Bind();

    float f = 1.0f * WIDTH / HEIGHT;
    Mat4<> proj = Mat4<>::Ortho(-f, f, -1.0f, 1.0f, -1.0f, 1.0f);
    // Mat4<> proj = Mat4<>::Perspective(90.0f, 16.0f / 9.0f, -0.5f, -1.0f);

    Texture texture("res/textures/cpp_logo.png");

	float g = 0.0f;

    float xPos = 0.0f;
    float yPos = 0.0f;

    Renderable<unsigned int> renderable(va, ib, shader);
    float prevTime = 0;
    float newTime = static_cast<float>(glfwGetTime());
    float deltaTime;

    Vec3<> axis(1.0f, 0.0f, 0.0f);
    Quaternion<> quaternion(axis, 90.0f);
    Vec3<> target(0.0f, 1.0f, 0.0f);
    Vec3<> result = quaternion * target;
    std::cout << result << std::endl;

	while (!window->ShouldClose()) {
        deltaTime = newTime - prevTime;
        prevTime = newTime;
		window->PollEvents();
        Renderer<unsigned int>::Clear();

        Vec2<int> mousePos;
        gameEventHandler.GetMousePosition(mousePos);
        Vec2<> mousePosf = Vec2<>(map(mousePos.x, 0, WIDTH, -f, f),
                                  map(mousePos.y, HEIGHT, 0, -1.0f, 1.0f));

        renderable.GetShader().SetUniform2f("u_LightPos", mousePosf.x,
                                            mousePosf.y);

        renderable.GetShader().SetUniformMat4f("u_Proj", proj);
		float s = sinf(g);
        renderable.GetShader().SetUniform4f("u_Color", 0.5f + s / 3, 0.3f,
                                            0.5f + cosf(g) / 3, 1.0f);

        xPos += horizontal.GetAmount() * deltaTime;
        yPos += vertical.GetAmount() * deltaTime;

        Mat4<> scale = Mat4<>::Scale(Vec3<>(0.2f + s / 8));
        Mat4<> model = Mat4<>::Translation(Vec3<>(xPos, yPos, 0.0f)) * scale;
        shader.SetUniformMat4f("u_Model", model);

		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

        renderer.Submit(renderable);

        renderer.Flush();

        window->SwapBuffers();

        g += 0.05;
        newTime = static_cast<float>(glfwGetTime());
    }
}
