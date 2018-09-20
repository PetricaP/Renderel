#include "Window.hpp"

namespace renderel {

Window::Window(int32 width, int32 height, EventHandler *handler, GUI *gui)
	: m_Width(width), m_Height(height), m_EventHandler(handler), m_GUI(gui) {}

Window::~Window() {
	delete m_EventHandler;
	delete m_GUI;
}

} // namespace renderel
