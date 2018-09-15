#ifndef IMGUI_HPP
#define IMGUI_HPP

#include "GUI.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace renderel {

// TODO: make ImGUI a singleton
class ImGUI : public GUI {
  public:
	ImGUI(void *windowHandle, const std::string &glslVersion);
	/* Call this destructor before glfwTerminate() */
	~ImGUI() override;
	void Init() override;
	void Begin(const std::string &name) override;
	void End() override;
	void Render() override;
	bool Button(const std::string &name) override;
};

} // namespace renderel

#endif // IMGUI_HPP
