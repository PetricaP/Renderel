#include "Window.hpp"
#include <GL/glew.h>

namespace renderel {

Window::Window(int width, int height) : m_Width(width), m_Height(height) {}

void Window::SetClearColor(float r, float g, float b) const {
    glClearColor(r, g, b, 1.0f);
}

} // namespace renderel
