#ifndef GRAPHICS_VERTEXBUFFER_HPP
#define GRAPHICS_VERTEXBUFFER_HPP

namespace renderel::graphics {

class VertexBuffer {
  private:
	unsigned int m_RendererID;

  public:
	VertexBuffer(void *data, unsigned int size);
	VertexBuffer(const void *data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};

} // namespace renderel::graphics

#endif // GRAPHICS_VERTEXBUFFER_HPP
