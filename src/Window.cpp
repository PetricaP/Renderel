#include "Window.hpp"

namespace renderel {

Window::Window(int32 width, int32 height, EventHandler *handler)
	: m_Width(width), m_Height(height), m_EventHandler(handler) {}

} // namespace renderel
