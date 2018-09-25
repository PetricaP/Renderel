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

void VertexArray::AddBuffer(std::unique_ptr<VertexBuffer> vb,
							const VertexBufferLayout &layout) {
	Bind();
	vb->Bind();
	m_Count += vb->GetCount();
	const auto &elements = layout.GetElements();
	unsigned long offset = 0;
	for (uint32 i = 0; i < elements.size(); ++i) {
		const auto &element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, static_cast<int32>(element.count),
									 element.type, element.normalized,
									 static_cast<int32>(layout.GetStride()),
									 (const void *)offset));
		offset +=
			element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	m_VBs.push_back(std::move(vb));
}

void VertexArray::AddBuffers(std::vector<std::unique_ptr<VertexBuffer>> vbs,
							 const VertexBufferLayout &layout) {
	for (auto &vb : vbs) {
		AddBuffer(std::move(vb), layout);
	}
}

} // namespace renderel::graphics
