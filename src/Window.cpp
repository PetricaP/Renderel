#include "Window.hpp"

namespace renderel {

Window::Window(int width, int height, const EventHandler *handler)
    : m_Width(width), m_Height(height), m_EventHandler(handler) {}

} // namespace renderel
