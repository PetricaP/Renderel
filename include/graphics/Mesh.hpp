#ifndef MESH_HPP
#define MESH_HPP

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "graphics/OBJLoader.hpp"
#include "graphics/Vertex.hpp"
#include <string>

namespace renderel::graphics {

template <typename T = unsigned int, typename F = float>
class Mesh {
  private:
	VertexArray *m_VA = nullptr;
	IndexBuffer<T> *m_IB = nullptr;

  public:
	Mesh(const std::string &objFilePath, bool loadTextures = false,
		 bool loadNormals = false);
	~Mesh();

	void SetIndexBuffer(IndexBuffer<T> *ib) { m_IB = ib; }
	IndexBuffer<T> *GetIndexBuffer() const { return m_IB; }
	void SetVertexArray(VertexArray *va) { m_VA = va; }
	VertexArray *GetVertexArray() const { return m_VA; }
};

template <typename T, typename F>
Mesh<T, F>::Mesh(const std::string &objFilePath, bool loadTextures,
				 bool loadNormals) {

	vector<Vertex<F>> vertices;
	vector<T> indices;

	OBJLoader::Load<T, F>(objFilePath, vertices, indices, loadTextures,
						  loadNormals);

	if (loadNormals) {
		OBJLoader::computeTangents(vertices, indices);
	}

	m_VA = new VertexArray();

	VertexBuffer *vb = new VertexBuffer(
		vertices.data(),
		static_cast<unsigned int>(vertices.size() * sizeof(Vertex<F>)));

	VertexBufferLayout vbl;
	// Position
	vbl.Push<F>(3);
	// if (loadTextures) {

	// TexCoord
	vbl.Push<F>(2);

	//}
	// if (loadNormals) {

	// Normal
	vbl.Push<F>(3);
	// Tangent
	vbl.Push<F>(3);
	// Bitangent
	vbl.Push<F>(3);

	//}

	m_VA->AddBuffer(vb, vbl);

	m_IB = new IndexBuffer<T>(indices.data(),
							  static_cast<unsigned int>(indices.size()));
}

template <typename T, typename F>
Mesh<T, F>::~Mesh() {
	delete m_VA;
	delete m_IB;
}

} // namespace renderel::graphics

#endif // MESH_HPP
