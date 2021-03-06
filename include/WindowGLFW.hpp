#ifndef WINDOWGLFW_HPP
#define WINDOWGLFW_HPP

#include "EventHandler.hpp"
#include "Window.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using APIWindowHandleGLFW = GLFWwindow *;

namespace renderel {

class WindowGLFW final : public Window {
  private:
	GLFWwindow *m_GLFWwindow = nullptr;

  public:
	WindowGLFW(int width, int height, std::string title,
			   EventHandler *eventHandler);
	~WindowGLFW() override;

	bool ShouldClose() const override;
	void SwapBuffers() const override;
	void PollEvents() const override;
	void *GetAPIHandle() const override { return m_GLFWwindow; }
};

} // namespace renderel

#endif // WINDOWGLFW_HPP
