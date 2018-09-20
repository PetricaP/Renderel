#ifndef GRAPHICS_VERTEXBUFFERLAYOUT_HPP
#define GRAPHICS_VERTEXBUFFERLAYOUT_HPP

#include "Debug.hpp"
#include "GL/glew.h"
#include "core/Common.hpp"
#include <vector>

namespace renderel::graphics {

struct VertexBufferElement {
	uint32 type;
	uint32 count;
	bool normalized;

	static uint32 GetSizeOfType(uint32 type) {
		switch (type) {
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
  private:
	std::vector<VertexBufferElement> m_Elements;
	uint32 m_Stride = 0;

  public:
	VertexBufferLayout() = default;
	template <typename T>
	void Push(uint32 count);

	const std::vector<VertexBufferElement> GetElements() const {
		return m_Elements;
	}

	uint32 GetStride() const { return m_Stride; }
};

template <>
inline void VertexBufferLayout::Push<float>(uint32 count) {
	m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::Push<int32>(uint32 count) {
	m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_INT);
}

template <>
inline void VertexBufferLayout::Push<uint32>(uint32 count) {
	m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::Push<unsigned char>(uint32 count) {
	m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

} // namespace renderel::graphics

#endif // GRAPHICS_VERTEXBUFFERLAYOUT_HPP
