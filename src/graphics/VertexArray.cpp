#include "graphics/VertexArray.hpp"
#include "GL/glew.h"

namespace renderel::graphics {

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_RendererID)); }

void VertexArray::Bind() const { GLCall(glBindVertexArray(m_RendererID)); }

void VertexArray::Unbind() const { GLCall(glBindVertexArray(0)); }

void VertexArray::AddBuffer(const VertexBuffer &vb,
							const VertexBufferLayout &layout) const {
	Bind();
	vb.Bind();
	const auto &elements = layout.GetElements();
	unsigned long offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto &element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, static_cast<int>(element.count),
                                     element.type, element.normalized,
                                     static_cast<int>(layout.GetStride()),
                                     (const void *)offset));
		offset +=
			element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

} // namespace renderel::graphics
