#include "ImGUI.hpp"

namespace renderel {

ImGUI::ImGUI(void *windowHandle, const std::string &glslVersion) {
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(windowHandle),
								 false);
	ImGui_ImplOpenGL3_Init(glslVersion.c_str());
	ImGui::StyleColorsDark();
}

void ImGUI::Init() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

ImGUI::~ImGUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool ImGUI::Button(const std::string &name) {
	return ImGui::Button(name.c_str());
}

void ImGUI::Begin(const std::string &name) { ImGui::Begin(name.c_str()); }

void ImGUI::End() { ImGui::End(); }

void ImGUI::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace renderel
