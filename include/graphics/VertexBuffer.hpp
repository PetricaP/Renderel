#ifndef GRAPHICS_VERTEXBUFFER_HPP
#define GRAPHICS_VERTEXBUFFER_HPP

#include "core/Common.hpp"
#include "math/Vec3.hpp"
#include <vector>

namespace renderel::graphics {

struct PVertex {
	math::Vec3<> position;
	PVertex(math::Vec3<> position) : position(position) {}
};

class VertexBuffer {
  private:
	uint32 m_RendererID = 0;
	uint32 m_Count = 0;

  public:
	VertexBuffer(void *vertices, uint32 count, uint32 vertexSize);
	VertexBuffer(const void *vertices, uint32 count, uint32 vertexSize);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	uint32 GetCount() const { return m_Count; }
};

} // namespace renderel::graphics

#endif // GRAPHICS_VERTEXBUFFER_HPP
