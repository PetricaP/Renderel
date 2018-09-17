#ifndef TESTCLEARCOLOR_HPP
#define TESTCLEARCOLOR_HPP

#include "math/Vec4.hpp"
#include "test/Test.hpp"

namespace renderel::test {

class TestClearColor : public Test {

  private:
	math::Vec4<> m_Color;

  public:
	TestClearColor();
	~TestClearColor() override;

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnGUIRender() override;
};

} // namespace renderel::test

#endif // !TESTCLEARCOLOR_HPP
