#include "graphics/Renderer.hpp"
#include "Debug.hpp"
#include <GL/glew.h>

namespace renderel::graphics {

void Renderer::InitGraphics() {
	if (glewInit() != GLEW_OK) {
		std::cerr << "Couldn't initialize glew.\n";
		exit(EXIT_FAILURE);
	}

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
}

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::SetClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

} // namespace renderel::graphics
