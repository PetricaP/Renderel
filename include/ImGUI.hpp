#ifndef IMGUI_HPP
#define IMGUI_HPP

#include "GUI.hpp"

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
	void Text(const char *message, ...) override;
	void Slider3f(const char *name, float *memory, float minValue,
				  float maxValue) override;
	void Sliderf(const char *name, float *memory, float minValue,
				 float maxValue) override;
	void ColorEdit4(const char *name, float *memory) override;
};

} // namespace renderel

#endif // IMGUI_HPP
