#include "graphics/IndexBuffer.hpp"
#include "Debug.hpp"
#include <GL/glew.h>

namespace renderel::graphics {

IndexBuffer::IndexBuffer(void *data, uint32 count) : m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						static_cast<int32>(count * sizeof(uint32)), data,
						GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const void *data, uint32 count) : m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						static_cast<int32>(count * sizeof(uint32)), data,
						GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() { GLCall(glDeleteBuffers(1, &m_RendererID)); }

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace renderel::graphics
