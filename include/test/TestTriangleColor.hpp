#ifndef TESTTRIANGLECOLOR_HPP
#define TESTTRIANGLECOLOR_HPP

#include "graphics/BasicRenderer.hpp"
#include "math/Vec4.hpp"
#include "test/Test.hpp"

namespace renderel::test {

class TestTriangleColor : public Test {

  private:
	math::Vec4<float> m_Colors[3];

	static constexpr float size = 0.5f;

	static constexpr float m_Vertices[] = {
		0.0f,  size,  0.0f, 0.0f, // First corner
		-size, -size, 0.0f, 1.0f, // Second corner
		size,  -size, 0.0f, 2.0f  // Third corner
	};

	static constexpr int m_Indices[] = {0, 1, 2};

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
