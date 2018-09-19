#ifndef TESTFACECULLING_HPP
#define TESTFACECULLING_HPP

#include "Transform.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/Texture.hpp"
#include "math/Vec4.hpp"
#include "test/Test.hpp"

namespace renderel::test {

class TestFaceCulling : public Test {
  private:
	graphics::VertexArray *va = nullptr;
	graphics::IndexBuffer<> *ib = nullptr;
	graphics::Renderer<> *renderer = nullptr;
	graphics::Shader *shader = nullptr;
	graphics::Texture *texture = nullptr;

	math::Vec3<> rotation;
	Transform<> transform;

	math::Mat4<> model;
	math::Mat4<> proj;

  public:
	TestFaceCulling(const std::shared_ptr<Window> window);
	~TestFaceCulling() override;
	void OnRender() override;
	void OnGUIRender() override;
	void OnUpdate(float deltaTime) override;
};

} // namespace renderel::test

#endif // !TESTFACECULLING_HPP
