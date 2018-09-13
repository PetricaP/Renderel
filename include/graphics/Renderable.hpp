#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "graphics/IndexBuffer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/VertexArray.hpp"

namespace renderel::graphics {

template <typename T = unsigned int>
class Renderable {
  private:
    const VertexArray &m_VA;
    const IndexBuffer<T> &m_IB;
    Shader &m_Shader;

  public:
    Renderable(const VertexArray &va, const IndexBuffer<T> &ib, Shader &shader)
        : m_VA(va), m_IB(ib), m_Shader(shader) {}
    ~Renderable() = default;

    const VertexArray &GetVA() const { return m_VA; }
    const IndexBuffer<T> &GetIB() const { return m_IB; }
    Shader &GetShader() const { return m_Shader; }
};

} // namespace renderel::graphics

#endif // RENDERABLE_HPP
