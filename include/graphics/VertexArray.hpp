#ifndef GRAPHICS_VERTEXARRAY_HPP
#define GRAPHICS_VERTEXARRAY_HPP

#include "core/Common.hpp"
#include "graphics/VertexBuffer.hpp"
#include "graphics/VertexBufferLayout.hpp"
#include <memory>
#include <vector>

namespace renderel::graphics {

class VertexArray {
  private:
	uint32 m_RendererID;
	std::vector<std::unique_ptr<VertexBuffer>> m_VBs;

  public:
	VertexArray();
	~VertexArray();
	void AddBuffer(std::unique_ptr<VertexBuffer> vb,
				   const VertexBufferLayout &layout);
	void AddBuffers(std::vector<std::unique_ptr<VertexBuffer>> vbs,
					const VertexBufferLayout &layout);

	void Bind() const;
	void Unbind() const;
};

} // namespace renderel::graphics

#endif // GRAPHICS_VERTEXARRAY_HPP
