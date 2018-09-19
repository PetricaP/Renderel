#ifndef MESH_HPP
#define MESH_HPP

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "graphics/OBJLoader.hpp"
#include <string>

namespace renderel::graphics {

template <typename T = unsigned int, typename F = float>
class Mesh {
  private:
	VertexArray *m_VA = nullptr;
	IndexBuffer<T> *m_IB = nullptr;

  public:
	Mesh(const std::string &objFilePath);
	~Mesh();

	void SetIndexBuffer(IndexBuffer<T> *ib) { m_IB = ib; }
	IndexBuffer<T> *GetIndexBuffer() const { return m_IB; }
	void SetVertexArray(VertexArray *va) { m_VA = va; }
	VertexArray *GetVertexArray() const { return m_VA; }
};

template <typename T, typename F>
Mesh<T, F>::Mesh(const std::string &objFilePath) {
	OBJLoader::Load<T, F>(objFilePath, m_IB, m_VA);
}

template <typename T, typename F>
Mesh<T, F>::~Mesh() {
	delete m_VA;
	delete m_IB;
}

} // namespace renderel::graphics

#endif // MESH_HPP
