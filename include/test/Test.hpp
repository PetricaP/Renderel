#ifndef TEST_HPP
#define TEST_HPP

#include "Window.hpp"
#include <functional>
#include <memory>

namespace renderel::test {

class Test {
  protected:
	const std::shared_ptr<Window> m_Window;

  public:
	Test(const std::shared_ptr<Window> window) : m_Window(window) {}
	virtual ~Test() = default;

	virtual void OnUpdate(float) {}
	virtual void OnRender() {}
	virtual void OnGUIRender() {}
};

struct TestFunctionAndName {
	std::string name;
	std::function<std::shared_ptr<Test>()> function;
};

class TestMenu : public Test {
  private:
	std::shared_ptr<Test> &m_CurrentTest;
	std::vector<TestFunctionAndName> m_Tests;

  public:
	TestMenu(const std::shared_ptr<Window> window,
			 std::shared_ptr<Test> &currentTest);
	~TestMenu() override = default;

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnGUIRender() override;

	template <typename T>
	void RegisterTest(const std::string &testName) {

		TestFunctionAndName t = {
			testName,
			[this]() { return std::shared_ptr<Test>(new T(m_Window)); }};

		m_Tests.push_back(t);
	}
};

} // namespace renderel::test

#endif // !TEST_HPP
