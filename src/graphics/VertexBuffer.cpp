#include "graphics/VertexBuffer.hpp"
#include "Debug.hpp"
#include "GL/glew.h"

namespace renderel::graphics {

VertexBuffer::VertexBuffer(void *vertices, uint32 count, uint32 vertexSize)
	: m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * vertexSize, vertices,
						GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const void *vertices, uint32 count,
						   uint32 vertexSize)
	: m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * vertexSize, vertices,
						GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() { GLCall(glDeleteBuffers(1, &m_RendererID)); }

void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const { GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

} // namespace renderel::graphics
