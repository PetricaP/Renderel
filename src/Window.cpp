#include "Window.hpp"

namespace renderel {

Window::Window(int32 width, int32 height, std::unique_ptr<EventHandler> handler)
	: m_Width(width), m_Height(height), m_EventHandler(std::move(handler)) {}

} // namespace renderel
