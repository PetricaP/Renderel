#ifndef GRAPHICS_VERTEXBUFFER_HPP
#define GRAPHICS_VERTEXBUFFER_HPP

class VertexBuffer {
  private:
    unsigned int m_RendererID;

  public:
    VertexBuffer(void *data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
};

#endif // GRAPHICS_VERTEXBUFFER_HPP
