#include "Debug.hpp"
#include "GL/glew.h"
#include "WindowGLFW.hpp"
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

int main() {
    std::unique_ptr<Window> window =
        std::make_unique<WindowGLFW>(WIDTH, HEIGHT, "Hello");
    window->SetClearColor(0.1f, 0.1f, 0.1f);

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

    Mat4<float> proj =
        Mat4<float>::Ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
    shader.SetUniformMat4f("u_Proj", proj);

    Mat4<float> model =
        Mat4<float>::Translation(Vec3<float>(WIDTH / 4, HEIGHT / 4, 0.0f));
    shader.SetUniformMat4f("u_Model", model);

	float g = 0.0f;
    while (!window->ShouldClose()) {
        window->PollEvents();
        window->Clear();

        Vec2<double> mousePos;
        glfwGetCursorPos(static_cast<GLFWwindow *>(window->GetAPIwindow()),
                         &mousePos.x, &mousePos.y);
        shader.SetUniform2f("u_LightPos", static_cast<float>(mousePos.x),
                            static_cast<float>(mousePos.y));

        shader.SetUniformMat4f("u_Proj", proj);

		va.Bind();
		shader.Bind();
		ib.Bind();

        shader.SetUniform4f("u_Color", 0.5f + sinf(g) / 2, 0.3f, 0.4f, 1.0f);

        GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT,
                              nullptr));

        window->SwapBuffers();
		g += 0.1;
	}
}
