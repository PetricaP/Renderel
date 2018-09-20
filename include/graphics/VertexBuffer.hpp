#ifndef GRAPHICS_VERTEXBUFFER_HPP
#define GRAPHICS_VERTEXBUFFER_HPP

#include "core/Common.hpp"

namespace renderel::graphics {

class VertexBuffer {
  private:
	uint32 m_RendererID;

  public:
	VertexBuffer(void *data, uint32 size);
	VertexBuffer(const void *data, uint32 size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};

} // namespace renderel::graphics

#endif // GRAPHICS_VERTEXBUFFER_HPP
