#ifndef GRAPHICS_INDEXBUFFER_HPP
#define GRAPHICS_INDEXBUFFER_HPP

#include "Debug.hpp"
#include "GL/glew.h"
#include "core/Common.hpp"
#include <type_traits>

namespace renderel::graphics {

class IndexBuffer {
  private:
	uint32 m_RendererID = 0;
	uint32 m_Count = 0;

  public:
	IndexBuffer(void *data, uint32 count);
	IndexBuffer(const void *data, uint32 count);

	~IndexBuffer();
	void Bind() const;
	void Unbind() const;

	static uint32 GetType() { return GL_UNSIGNED_INT; }
	uint32 GetCount() const { return m_Count; }
};
} // namespace renderel::graphics

#endif // GRAPHICS_INDEXBUFFER_HPP
