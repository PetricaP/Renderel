#include "Debug.hpp"
#include "GameEventHandler.hpp"
#include "InputControl.hpp"
#include "WindowGLFW.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/Mat4.hpp"
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
    gameEventHandler.AddKeyControl(GLFW_KEY_W, vertical, -1.0f);
    gameEventHandler.AddKeyControl(GLFW_KEY_S, vertical, 1.0f);

    Window *window =
        new APIWindow(WIDTH, HEIGHT, "Renderel", &gameEventHandler);

    Renderer<unsigned int>::InitGraphics();
    Renderer<unsigned int>::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    BasicRenderer<unsigned int> renderer;

	float vertices[] = {
		0.0f,		   0.0f,		  0.0f, 0.0f, // 0
		HEIGHT / 2.0f, 0.0f,		  1.0f, 0.0f, // 2
		0.0f,		   HEIGHT / 2.0f, 0.0f, 1.0f, // 1
        HEIGHT / 2.0f, HEIGHT / 2.0f, 1.0f, 1.0f  // 3
	};

    unsigned int indices[] = {
		0, 1, 2, // first triangle
		1, 2, 3  // second triangle
	};

	VertexArray va;

	VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(2);
	layout.Push<float>(2);

    va.AddBuffer(&vb, layout);

    IndexBuffer<unsigned int> ib(indices, sizeof(indices) / sizeof(indices[0]));

	Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

	shader.Bind();

	Mat4<> proj = Mat4<>::Ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
	shader.SetUniformMat4f("u_Proj", proj);

	Texture texture("res/textures/cpp_logo.png");

	float g = 0.0f;

    float xPos = 0.0f;
    float yPos = 0.0f;

    Renderable<unsigned int> renderable(va, ib, shader);
    float prevTime = 0;
    float newTime = static_cast<float>(glfwGetTime());
    float deltaTime;
	while (!window->ShouldClose()) {
        deltaTime = newTime - prevTime;
        prevTime = newTime;
		window->PollEvents();
        Renderer<unsigned int>::Clear();

        Vec2<int> mousePos;
        gameEventHandler.GetMousePosition(mousePos);

        renderable.GetShader().SetUniform2f("u_LightPos",
                                            static_cast<float>(mousePos.x),
                                            static_cast<float>(mousePos.y));
		renderable.GetShader().SetUniformMat4f("u_Proj", proj);
		float s = sinf(g);
		renderable.GetShader().SetUniform4f("u_Color", 0.5f + s / 2, 0.3f,
											0.5f + cosf(g) / 2, 1.0f);

        xPos += horizontal.GetAmount() * 100 * deltaTime;
        yPos += vertical.GetAmount() * 100 * deltaTime;

        Mat4<> model = Mat4<>::Translation(Vec3<>(xPos, yPos, 0.0f));
		shader.SetUniformMat4f("u_Model", model);

		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

        renderer.Submit(renderable);

        renderer.Flush();
		window->SwapBuffers();
		g += 0.1;
        newTime = static_cast<float>(glfwGetTime());
    }
}
