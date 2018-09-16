#ifndef GRAPHICS_INDEXBUFFER_HPP
#define GRAPHICS_INDEXBUFFER_HPP

#include "Debug.hpp"
#include "GL/glew.h"
#include <type_traits>

namespace renderel::graphics {

template <typename T = unsigned int>
class IndexBuffer {
  private:
	unsigned int m_RendererID;
	unsigned int m_Count;

  public:
	IndexBuffer(void *data, unsigned int count);
	IndexBuffer(const void *data, unsigned int count);

	~IndexBuffer();
	void Bind() const;
	void Unbind() const;

	template <typename U = T>
	static typename std::enable_if<std::is_same<U, unsigned int>::value,
								   unsigned int>::type
	GetType() {
		return GL_UNSIGNED_INT;
	}

	template <typename U = T>
	static typename std::enable_if<std::is_same<U, unsigned char>::value,
								   unsigned int>::type
	GetType() {
		return GL_UNSIGNED_BYTE;
	}

	template <typename U = T>
	static
		typename std::enable_if<std::is_same<U, int>::value, unsigned int>::type
		GetType() {
		return GL_INT;
	}

	unsigned int GetCount() const { return m_Count; }
};

template <typename T>
IndexBuffer<T>::IndexBuffer(void *data, unsigned int count) : m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data,
						GL_STATIC_DRAW));
}

template <typename T>
IndexBuffer<T>::IndexBuffer(const void *data, unsigned int count)
	: m_Count(count) {
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
