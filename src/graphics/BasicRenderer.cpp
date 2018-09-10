#include "graphics/BasicRenderer.hpp"
#include "Debug.hpp"
#include <GL/glew.h>

namespace renderel::graphics {

void BasicRenderer::Flush() {
    while (!m_RenderObjects.empty()) {
        const Renderable &renderable = m_RenderObjects.front();
        renderable.GetVA().Bind();
        renderable.GetIB().Bind();
        renderable.GetShader().Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6 * sizeof(unsigned int),
                              GL_UNSIGNED_INT, nullptr));
        m_RenderObjects.pop();
    }
}

void BasicRenderer::Submit(const Renderable &renderable) {
    m_RenderObjects.push(renderable);
}

} // namespace renderel::graphics
