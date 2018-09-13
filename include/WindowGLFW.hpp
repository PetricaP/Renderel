#ifndef WINDOWGLFW_HPP
#define WINDOWGLFW_HPP

#include "EventHandler.hpp"
#include "Window.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace renderel {

class WindowGLFW final : public Window {
  private:
	GLFWwindow *m_GLFWwindow = nullptr;

  public:
    WindowGLFW(int width, int height, std::string title,
               EventHandler *eventHandler);
    virtual ~WindowGLFW() override;

	virtual void *GetAPIWindowHandle() override { return m_GLFWwindow; }

	virtual bool ShouldClose() const override;
	virtual void SwapBuffers() const override;
    virtual void PollEvents() const override;
};

} // namespace renderel

#endif
