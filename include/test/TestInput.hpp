#ifndef TESTINPUT_HPP
#define TESTINPUT_HPP

#include "GameEventHandler.hpp"
#include "Test.hpp"
#include "Transform.hpp"
#include "graphics/BasicRenderer.hpp"

namespace renderel::test {

class TestInput : public Test {
  private:
	GameEventHandler *handler = nullptr;

	InputControl xAxis;
	InputControl yAxis;
	InputControl zAxis;
	InputControl xRotation;
	InputControl yRotation;
	InputControl zRotation;

	static constexpr float vertices[] = {
		-0.5f, -0.5f, 0.0f, // 0
		0.0f,  0.5f,  0.0f, // 1
		0.5f,  -0.5f, 0.0f  // 2
	};

	static constexpr uint32 indices[] = {0, 1, 2};

	math::Vec3<> rotation = math::Vec3(0.0f);

	Transform<> transform;

	graphics::VertexArray *va = nullptr;
	graphics::IndexBuffer<> *ib = nullptr;
	graphics::Shader *shader = nullptr;

  public:
	TestInput(const Window &window);
	~TestInput() override;

	void OnUpdate(float) override;
	void OnRender() override;
	void OnGUIRender() override;
};

} // namespace renderel::test

#endif // TESTINPUT_HPP
