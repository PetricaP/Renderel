#include "test/TestClearColor.hpp"

#include "Debug.hpp"
#include "graphics/Renderer.hpp"
#include <imgui.h>

namespace renderel::test {

TestClearColor::TestClearColor(const std::shared_ptr<Window> window)
	: Test(window), m_Color{0.75f, 0.75f, 0.75f, 1.0f} {}

TestClearColor::~TestClearColor() {}

void TestClearColor::OnUpdate(float) {}

void TestClearColor::OnRender() {
	graphics::Renderer<>::SetClearColor(m_Color.r, m_Color.g, m_Color.b,
										m_Color.a);
	graphics::Renderer<>::Clear();
}

void TestClearColor::OnGUIRender() {
	ImGui::ColorEdit4("Pick a color", m_Color.elements);
}

} // namespace renderel::test
