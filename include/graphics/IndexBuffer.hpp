#ifndef GRAPHICS_INDEXBUFFER_HPP
#define GRAPHICS_INDEXBUFFER_HPP

#include "Debug.hpp"
#include "GL/glew.h"
#include "core/Common.hpp"
#include <type_traits>

namespace renderel::graphics {

template <typename T = uint32>
class IndexBuffer {
  private:
	uint32 m_RendererID;
	uint32 m_Count;

  public:
	IndexBuffer(void *data, uint32 count);
	IndexBuffer(const void *data, uint32 count);

	~IndexBuffer();
	void Bind() const;
	void Unbind() const;

	template <typename U = T>
	static typename std::enable_if<std::is_same<U, uint32>::value, uint32>::type
	GetType() {
		return GL_UNSIGNED_INT;
	}

	template <typename U = T>
	static typename std::enable_if<std::is_same<U, unsigned char>::value,
								   uint32>::type
	GetType() {
		return GL_UNSIGNED_BYTE;
	}

	template <typename U = T>
	static typename std::enable_if<std::is_same<U, int32>::value, uint32>::type
	GetType() {
		return GL_INT;
	}

	uint32 GetCount() const { return m_Count; }
};

template <typename T>
IndexBuffer<T>::IndexBuffer(void *data, uint32 count) : m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data,
						GL_STATIC_DRAW));
}

template <typename T>
IndexBuffer<T>::IndexBuffer(const void *data, uint32 count) : m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data,
						GL_STATIC_DRAW));
}

template <typename T>
IndexBuffer<T>::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

template <typename T>
void IndexBuffer<T>::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

template <typename T>
void IndexBuffer<T>::Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace renderel::graphics

#endif // GRAPHICS_INDEXBUFFER_HPP
