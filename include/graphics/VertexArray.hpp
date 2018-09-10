#ifndef GRAPHICS_VERTEXARRAY_HPP
#define GRAPHICS_VERTEXARRAY_HPP

#include "graphics/VertexBuffer.hpp"
#include "graphics/VertexBufferLayout.hpp"
#include <vector>

namespace renderel::graphics {

class VertexArray {
  private:
	unsigned int m_RendererID;

  public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBuffer &vb,
				   const VertexBufferLayout &layout) const;
	void AddBuffers(std::vector<const VertexBuffer> vbs,
					const VertexBufferLayout &layout) const;

	void Bind() const;
	void Unbind() const;
};

} // namespace renderel::graphics

#endif // GRAPHICS_VERTEXARRAY_HPP
