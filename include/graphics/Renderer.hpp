#ifndef GRAPHICS_RENDERER_HPP
#define GRAPHICS_RENDERER_HPP

#include "graphics/Renderable.hpp"
#include <queue>

namespace renderel::graphics {

template <typename T = unsigned int>
class Renderer {
  public:
	Renderer() = default;

	virtual ~Renderer() = default;
	virtual void Flush() = 0;
	virtual void Submit(const Renderable<T> &renderable) = 0;

	static void InitGraphics();
	static void Clear();
	static void SetClearColor(float r, float g, float b, float a);
};

template <typename T>
void Renderer<T>::InitGraphics() {
	if (glewInit() != GLEW_OK) {
		std::cerr << "Couldn't initialize glew.\n";
		exit(EXIT_FAILURE);
	}

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glDepthFunc(GL_LESS));
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
}

template <typename T>
void Renderer<T>::Clear() {
	// TODO: GL_STENCIL_BIT
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template <typename T>
void Renderer<T>::SetClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

} // namespace renderel::graphics

#endif
