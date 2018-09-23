#ifndef MESH_HPP
#define MESH_HPP

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "graphics/OBJLoader.hpp"
#include <string>

namespace renderel::graphics {

template <typename T = uint32, typename F = float>
class Mesh {
  private:
	std::unique_ptr<VertexArray> m_VA = nullptr;
	std::unique_ptr<IndexBuffer<T>> m_IB = nullptr;

  public:
	Mesh() = default;
	Mesh(const std::string &objFilePath);
	~Mesh();

	void LoadOBJ(const std::string &objFilePath);

	void SetIndexBuffer(std::unique_ptr<IndexBuffer<T>> ib) {
		m_IB = std::move(ib);
	}
	IndexBuffer<T> *GetIndexBuffer() const { return m_IB.get(); }

	std::unique_ptr<IndexBuffer<T>> *GetMIndexBuffer() {
		return std::move(m_IB);
	}

	void SetVertexArray(std::unique_ptr<VertexArray> va) {
		m_VA = std::move(va);
	}
	VertexArray *GetVertexArray() const { return m_VA.get(); }

	// TODO: This is not really a solution to our problem, just code that
	// makes everything work
	Mesh(Mesh &other)
		: m_VA(other.m_VA.release()), m_IB(other.m_IB.release()) {}
};

template <typename T, typename F>
Mesh<T, F>::Mesh(const std::string &objFilePath) {
	OBJLoader::Load<T, F>(objFilePath, m_IB, m_VA);
}

template <typename T, typename F>
void Mesh<T, F>::LoadOBJ(const std::string &objFilePath) {
	OBJLoader::Load<T, F>(objFilePath, m_IB, m_VA);
}

template <typename T, typename F>
Mesh<T, F>::~Mesh() {}

} // namespace renderel::graphics

#endif // MESH_HPP
