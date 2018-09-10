#ifndef BASICRENDERER_HPP
#define BASICRENDERER_HPP

#include "graphics/Renderer.hpp"

namespace renderel::graphics {

class BasicRenderer : public Renderer {
  public:
    BasicRenderer() = default;
    virtual ~BasicRenderer() override = default;
    virtual void Flush() override;
    virtual void Submit(const Renderable &renderable) override;
};

} // namespace renderel::graphics

#endif // BASICRENDERER_HPP
