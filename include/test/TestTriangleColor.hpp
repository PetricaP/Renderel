#ifndef TESTTRIANGLECOLOR_HPP
#define TESTTRIANGLECOLOR_HPP

#include "graphics/BasicRenderer.hpp"
#include "math/Vec4.hpp"
#include "test/Test.hpp"

namespace renderel::test {

struct VertexI {
	float x, y, z;
	int32 index;
};

class TestTriangleColor : public Test {

  private:
	math::Vec4<float> m_Colors[3];

	static constexpr float size = 0.5f;

	static constexpr VertexI m_Vertices[] = {
		{0.0f, size, 0.0f, 0},   // First corner
		{-size, -size, 0.0f, 1}, // Second corner
		{size, -size, 0.0f, 2}   // Third corner
	};

	static constexpr int32 m_Indices[] = {0, 1, 2};

	graphics::VertexArray *va;
	graphics::VertexBuffer *vb;
	graphics::IndexBuffer<> *ib;
	graphics::Renderer<> *renderer;
	graphics::Shader *shader;

  public:
	TestTriangleColor(const std::shared_ptr<Window> window);
	~TestTriangleColor() override;

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnGUIRender() override;
};

} // namespace renderel::test

#endif // TESTTRIANGLECOLOR_HPP
