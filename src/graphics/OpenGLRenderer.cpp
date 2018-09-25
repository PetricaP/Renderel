#include "graphics/OpenGLRenderer.hpp"

namespace renderel::graphics {

void OpenGLRenderer::Flush() {
	while (!m_RenderObjects.empty()) {
		const Renderable &renderable = m_RenderObjects.front();
		renderable.shader.Bind();
		renderable.va->Bind();
		if (renderable.ib == nullptr) {
			GLCall(glDrawArrays(GL_TRIANGLES, 0,
								static_cast<int32>(renderable.va->GetCount())));
		} else {
			renderable.ib->Bind();
			GLCall(glDrawElements(GL_TRIANGLES,
								  static_cast<int32>(renderable.ib->GetCount()),
								  IndexBuffer::GetType(), nullptr));
		}
		m_RenderObjects.pop();
	}
}

void OpenGLRenderer::Submit(const Renderable &renderable) {
	m_RenderObjects.push(renderable);
}

void OpenGLRenderer::SetViewPort(int32 x1, int32 y1, int32 x2, int32 y2) {
	glViewport(x1, y1, x2, y2);
}

void OpenGLRenderer::EnableDepthMask() { GLCall(glDepthMask(GL_TRUE)); }

void OpenGLRenderer::DisableDepthMask() { GLCall(glDepthMask(GL_FALSE)); }

void OpenGLRenderer::InitGraphics() {
	if (glewInit() != GLEW_OK) {
		DEBUG_LOG("Renderer", ERROR, "Couldn't initialize GLEW.");
		exit(EXIT_FAILURE);
	}

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glDepthFunc(GL_LEQUAL));
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
}

void OpenGLRenderer::Clear() {
	// TODO: GL_STENCIL_BIT
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::SetClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

} // namespace renderel::graphics
