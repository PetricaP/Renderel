#ifndef GRAPHICS_VERTEXARRAY_HPP
#define GRAPHICS_VERTEXARRAY_HPP

#include "graphics/VertexBuffer.hpp"
#include "graphics/VertexBufferLayout.hpp"
#include <vector>

namespace renderel::graphics {

class VertexArray {
  private:
	unsigned int m_RendererID;
	std::vector<VertexBuffer *> m_VBs;

  public:
	VertexArray();
	~VertexArray();
	void AddBuffer(VertexBuffer *vb, const VertexBufferLayout &layout);
	void AddBuffers(std::vector<VertexBuffer *> vbs,
					const VertexBufferLayout &layout);

	void Bind() const;
	void Unbind() const;
};

} // namespace renderel::graphics

#endif // GRAPHICS_VERTEXARRAY_HPP
