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
	WindowGLFW(int32 width, int32 height, std::string title,
			   std::unique_ptr<EventHandler> eventHandler);
	~WindowGLFW() override;

	bool ShouldClose() const override;
	void SwapBuffers() const override;
	void PollEvents() const override;
	void *GetAPIHandle() const override { return m_GLFWwindow; }
	void DisableMouse() const override {
		glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	void EnableMouse() const override {
		glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	void Close() const override {
		glfwSetWindowShouldClose(m_GLFWwindow, GLFW_TRUE);
	}
};

} // namespace renderel

#endif // WINDOWGLFW_HPP
