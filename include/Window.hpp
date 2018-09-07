#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"
#include "GL/glew.h"
#include <string>

namespace renderel {

class Window {
  private:
    int m_Width;
    int m_Height;
    GLFWwindow *m_GLFWwindow;

  public:
    Window(int width, int height, std::string title);
    ~Window();

    bool ShouldClose() const;
    void Clear() const;
    void SwapBuffers() const;
    void PollEvents() const;
    void SetClearColor(float r, float g, float b);

    int getWidth() const { return m_Width; }
    int getHeight() const { return m_Width; }
};

} // namespace renderel

#endif // WINDOW_HPP
