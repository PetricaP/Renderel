#pragma once

#include "Window.hpp"
#include "math/Vec4.hpp"
#include "test/Test.hpp"

namespace renderel::test {

class TestClearColor : public Test {

  private:
	math::Vec4<> m_Color;

  public:
	TestClearColor(const std::shared_ptr<Window> window);
	~TestClearColor() override;

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnGUIRender() override;
};

} // namespace renderel::test
