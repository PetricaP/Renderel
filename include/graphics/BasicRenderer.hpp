#ifndef BASICRENDERER_HPP
#define BASICRENDERER_HPP

#include "graphics/Renderer.hpp"

namespace renderel::graphics {

template <typename T = unsigned int>
class BasicRenderer : public Renderer<T> {
  private:
    std::queue<Renderable<T>> m_RenderObjects;

  public:
    BasicRenderer() = default;
    virtual ~BasicRenderer() override = default;
    virtual void Flush() override;
    virtual void Submit(const Renderable<T> &renderable) override;
};

template <typename T>
void BasicRenderer<T>::Flush() {
    while (!m_RenderObjects.empty()) {
        const Renderable<T> &renderable = m_RenderObjects.front();
        renderable.GetVA().Bind();
        renderable.GetIB().Bind();
        renderable.GetShader().Bind();
        GLCall(glDrawElements(GL_TRIANGLES, renderable.GetIB().GetCount(),
                              IndexBuffer<T>::GetType(), nullptr));
        m_RenderObjects.pop();
    }
}

template <typename T>
void BasicRenderer<T>::Submit(const Renderable<T> &renderable) {
    m_RenderObjects.push(renderable);
}

} // namespace renderel::graphics

#endif // BASICRENDERER_HPP
