#ifndef GRAPHICS_INDEXBUFFER_HPP
#define GRAPHICS_INDEXBUFFER_HPP

namespace renderel::graphics {

class IndexBuffer {
  private:
	unsigned int m_RendererID;

  public:
	IndexBuffer(void *data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
};

} // namespace renderel::graphics

#endif // GRAPHICS_INDEXBUFFER_HPP
