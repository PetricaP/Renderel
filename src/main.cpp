#include "Debug.hpp"
#include "GL/glew.h"
#include "Window.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include <iostream>

int main() {
	renderel::Window window(960, 540, "Hello");
	window.SetClearColor(0.8f, 0.8f, 0.0f);

	float positions[] = {
		0.5f,  -0.5f, // 0
		0.5f,  0.5f,  // 1
		-0.5f, -0.5f, // 2
		-0.5f, 0.5f   // 3
	};

	unsigned int indices[] = {0, 1, 2, 1, 2, 3};

	renderel::graphics::VertexArray va;
	renderel::graphics::VertexBuffer vb(positions, sizeof(positions));
	renderel::graphics::VertexBufferLayout layout;
	layout.Push<float>(2);

	va.AddBuffer(vb, layout);

	renderel::graphics::IndexBuffer ib(indices, sizeof(indices));

	renderel::graphics::Shader shader("shaders/vertexShader.glsl",
									  "shaders/fragmentShader.glsl");

	while (!window.ShouldClose()) {
		window.PollEvents();
		window.Clear();
		va.Bind();
		shader.Bind();
		ib.Bind();
		GLCall(
			glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0));
		window.SwapBuffers();
	}
}
