#ifndef TEST_HPP
#define TEST_HPP

#include "Window.hpp"
#include <functional>
#include <memory>

namespace renderel::test {

class Test {
  protected:
	const Window &m_Window;

  public:
	Test(const Window &window) : m_Window(window) {}
	virtual ~Test() = default;

	virtual void OnUpdate(float) {}
	virtual void OnRender() {}
	virtual void OnGUIRender() {}
};

} // namespace renderel::test

#endif // !TEST_HPP
