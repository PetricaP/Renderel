#ifndef GRAPHICS_RENDERER_HPP
#define GRAPHICS_RENDERER_HPP

#include "graphics/Renderable.hpp"
#include <queue>

namespace renderel::graphics {

class OpenGLRenderer {
  private:
	std::queue<Renderable> m_RenderObjects;

  public:
	OpenGLRenderer() = default;

	~OpenGLRenderer() = default;
	void Flush();
	void Submit(const Renderable &renderable);

	static void InitGraphics();
	static void Clear();
	static void SetClearColor(float r, float g, float b, float a);
	static void EnableDepthMask();
	static void DisableDepthMask();
	static void SetViewPort(int32 x1, int32 y1, int32 x2, int32 y2);
};

} // namespace renderel::graphics

#endif // GRAPHICS_RENDERER_HPP
