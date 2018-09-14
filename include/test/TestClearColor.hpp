#pragma once

#include "test/Test.hpp"
#include "math/Vec4.hpp"

namespace renderel::test {

class TestClearColor : public Test {

  private:
	math::Vec4<> m_Color;

  public:
	TestClearColor();
	~TestClearColor();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnGUIRender() override;
};

} // namespace renderel::test
