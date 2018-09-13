#include "graphics/VertexArray.hpp"
#include "GL/glew.h"

namespace renderel::graphics {

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
	for (auto vb : m_VBs) {
		delete vb;
	}
}

void VertexArray::Bind() const { GLCall(glBindVertexArray(m_RendererID)); }

void VertexArray::Unbind() const { GLCall(glBindVertexArray(0)); }

void VertexArray::AddBuffer(VertexBuffer *vb,
							const VertexBufferLayout &layout) {
	m_VBs.push_back(vb);
	Bind();
	vb->Bind();
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

void VertexArray::AddBuffers(std::vector<VertexBuffer *> vbs,
							 const VertexBufferLayout &layout) {
	for (auto vb : vbs) {
		AddBuffer(vb, layout);
	}
}

} // namespace renderel::graphics
