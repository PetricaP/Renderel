#ifndef GRAPHICS_RENDERER_HPP
#define GRAPHICS_RENDERER_HPP

#include "graphics/Renderable.hpp"
#include <queue>

namespace renderel::graphics {

class Renderer {
  protected:
    std::queue<Renderable> m_RenderObjects;

  public:
    Renderer() = default;

    virtual ~Renderer() = default;
    virtual void Flush() = 0;
    virtual void Submit(const Renderable &renderable) = 0;

    static void InitGraphics();
    static void Clear();
    static void SetClearColor(float r, float g, float b, float a);
};

} // namespace renderel::graphics

#endif
