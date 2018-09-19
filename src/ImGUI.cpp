#include "ImGUI.hpp"

namespace renderel {

ImGUI::ImGUI(void *windowHandle, const std::string &glslVersion) {
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(windowHandle),
								 false);
	ImGui_ImplOpenGL3_Init(glslVersion.c_str());
	ImGui::StyleColorsDark();
	ImGuiStyle *style = &ImGui::GetStyle();
	ImVec4 *colors = style->Colors;

	colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	colors[ImGuiCol_Button] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.25f);
	// TODO
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
