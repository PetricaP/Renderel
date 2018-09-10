#include "Debug.hpp"
#include "GL/glew.h"
#include "WindowGLFW.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/Mat4.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
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
using APIWindowHandle = GLFWwindow *;

int main() {
    std::unique_ptr<Window> window =
        std::make_unique<APIWindow>(WIDTH, HEIGHT, "Hello");

    Renderer::InitGraphics();
    Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    std::unique_ptr<Renderer> renderer = std::make_unique<BasicRenderer>();

	float positions[] = {
        0.0f,		  0.0f,			 // 0
        WIDTH / 2.0f, 0.0f,			 // 2
        0.0f,		  HEIGHT / 2.0f, // 1
        WIDTH / 2.0f, HEIGHT / 2.0f  // 3
	};

    unsigned int indices[] = {
        0, 1, 2, // first triangle
        1, 2, 3  // second triangle
    };

	VertexArray va;

	VertexBuffer vb(positions, sizeof(positions));

	VertexBufferLayout layout;
	layout.Push<float>(2);

	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, sizeof(indices));

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

	shader.Bind();

    Mat4<> proj = Mat4<>::Ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
    shader.SetUniformMat4f("u_Proj", proj);

    Mat4<> model = Mat4<>::Translation(Vec3<>(WIDTH / 4, HEIGHT / 4, 0.0f));
    shader.SetUniformMat4f("u_Model", model);

	float g = 0.0f;
    Renderable renderable(va, ib, shader);
    while (!window->ShouldClose()) {
        window->PollEvents();
        Renderer::Clear();

        Vec2<double> mousePos;
        glfwGetCursorPos(
            static_cast<APIWindowHandle>(window->GetAPIWindowHandle()),
            &mousePos.x, &mousePos.y);

        renderable.GetShader().SetUniform2f("u_LightPos",
                                            static_cast<float>(mousePos.x),
                                            static_cast<float>(mousePos.y));
        renderable.GetShader().SetUniformMat4f("u_Proj", proj);
        renderable.GetShader().SetUniform4f("u_Color", 0.5f + sinf(g) / 2, 0.3f,
                                            0.4f, 1.0f);

        renderer->Submit(renderable);

        renderer->Flush();
        window->SwapBuffers();
		g += 0.1;
	}
}
