#pragma once

#include <functional>

namespace renderel::test {

class Test {
  public:
	Test() = default;
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
	TestMenu(std::shared_ptr<Test> &currentTest);
	~TestMenu() override = default;

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnGUIRender() override;

	template <typename T>
	void RegisterTest(const std::string &testName) {

		TestFunctionAndName t = {testName,
								 []() { return std::shared_ptr<Test>(new T); }};

		m_Tests.push_back(t);
	}
};

} // namespace renderel::test
