#include "test/Test.hpp"

#include <imgui.h>

namespace renderel::test {

	TestMenu::TestMenu(Test *&currentTest) : m_CurrentTest(currentTest) {

	}

	TestMenu::~TestMenu() {

	}

	void TestMenu::OnUpdate(float deltaTime) {
	}

	void TestMenu::OnRender() {
	}

	void TestMenu::OnGUIRender() {
		for (auto test : m_Tests) {
			if (ImGui::Button(test.name.c_str())) {
				m_CurrentTest = test.function();
			}
		}
	}

}