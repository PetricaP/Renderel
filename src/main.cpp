#include "Debug.hpp"
#include "GL/glew.h"
#include "Window.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/Mat4.hpp"
#include "math/Vec3.hpp"
#include <cmath>
#include <iostream>

using namespace renderel;
using namespace math;
using namespace graphics;

int main() {
	Window window(960, 540, "Hello");
	window.SetClearColor(0.1f, 0.1f, 0.1f);

	float positions[] = {
		0.5f,  -0.5f, // 0
		0.5f,  0.5f,  // 1
		-0.5f, -0.5f, // 2
		-0.5f, 0.5f   // 3
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
	shader.SetUniform2f("u_LightPos", 0.0f, 0.0f);

    Mat4<float> proj(1.0f);
    shader.SetUniformMat4f("u_Proj", proj);

	float g = 0.0f;
	while (!window.ShouldClose()) {
		window.PollEvents();
		window.Clear();

		va.Bind();
		shader.Bind();
		ib.Bind();

        shader.SetUniform4f("u_Color", 0.5f + sinf(g) / 2, 0.3f, 0.4f, 1.0f);

        GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT,
                              nullptr));

		window.SwapBuffers();
		g += 0.1;
	}
}
