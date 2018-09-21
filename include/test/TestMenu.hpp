#ifndef TESTMENU_HPP
#define TESTMENU_HPP

#include "Test.hpp"

namespace renderel::test {

struct TestFunctionAndName {
	std::string name;
	std::function<std::unique_ptr<Test>()> function;
};

/* TODO: The test menu shouldn't really be a Test */
class TestMenu : public Test {
  private:
	bool isActive = true;
	std::unique_ptr<Test> m_CurrentTest;
	std::vector<TestFunctionAndName> m_Tests;

  public:
	TestMenu(const Window &window);
	~TestMenu() override = default;

	void OnGUIRender() override;
	void Run(float deltaTime);

	template <typename T>
	void RegisterTest(const std::string &testName) {

		TestFunctionAndName t = {
			testName,
			[this]() { return std::move(std::make_unique<T>(m_Window)); }};

		m_Tests.push_back(t);
	}
};

} // namespace renderel::test

#endif // TESTMENU_HPP
