#include "test/Test.hpp"

#include <imgui.h>

namespace renderel::test {

TestMenu::TestMenu(std::shared_ptr<Test> &currentTest)
	: m_CurrentTest(currentTest) {}

void TestMenu::OnUpdate(float) {}

void TestMenu::OnRender() {}

void TestMenu::OnGUIRender() {
	for (auto test : m_Tests) {
		if (ImGui::Button(test.name.c_str())) {
			m_CurrentTest = test.function();
		}
	}
}

} // namespace renderel::test
