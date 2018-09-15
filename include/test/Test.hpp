#pragma once

#include <functional>

namespace renderel::test {

class Test {
  public:
	Test() = default;
	virtual ~Test() = default;

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnGUIRender() {}
};

struct TestWithName {
	std::string name;
	std::function<Test*()> function;
};

class TestMenu : public Test {
  private:
	Test *&m_CurrentTest;
	std::vector<TestWithName> m_Tests;

  public:
	TestMenu(Test *&currentTest);
	~TestMenu();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnGUIRender() override;

	template <typename T>
	void RegisterTest(const std::string &testName) {

		TestWithName t = {testName, []() { return new T(); }};

		m_Tests.push_back(t);
	}
};

} // namespace renderel::test
