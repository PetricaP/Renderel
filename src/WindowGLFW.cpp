#include "WindowGLFW.hpp"
#include "EventHandler.hpp"
#include "GlobalGLFWEventHandler.hpp"
#include <iostream>
#include <queue>
#include <unordered_map>

namespace renderel {

static void key_callback(GLFWwindow *window, int32 key, int32, int32 action,
						 int32) {
	Event event;
	event.type = KEY;
	event.keyEvent.key = static_cast<uint32>(key);
	event.keyEvent.action = static_cast<uint32>(action);
	GlobalGLFWEventHandler::PushEvent(window, event);
}

static void mouse_button_callback(GLFWwindow *window, int32 button,
								  int32 action, int32) {
	Event event;
	event.type = MOUSEBUTTON;
	event.mouseButtonEvent.button = static_cast<uint32>(button);
	event.mouseButtonEvent.action = static_cast<uint32>(action);
	GlobalGLFWEventHandler::PushEvent(window, event);
}

static void cursor_position_callback(GLFWwindow *window, double xPos,
									 double yPos) {
	Event event;
	event.type = MOUSEMOTION;
	event.mouseMotionEvent.xPos = static_cast<int32>(xPos);
	event.mouseMotionEvent.yPos = static_cast<int32>(yPos);
	GlobalGLFWEventHandler::PushEvent(window, event);
}

static void window_resize_callback(GLFWwindow *window, int32 width,
								   int32 height) {
	Event event;
	event.type = WINDOWRESIZE;
	event.windowEvent.width = width;
	event.windowEvent.height = height;
	GlobalGLFWEventHandler::PushEvent(window, event);
}

WindowGLFW::WindowGLFW(int32 width, int32 height, std::string title,
					   EventHandler *eventHandler, GUI *gui)
	: Window(width, height, eventHandler, gui) {

	// TODO: Create logging system for errors
	if (!glfwInit()) {
		std::cerr << "Couldn't initialize glfw" << std::endl;
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: implement flags for glfw window
	m_GLFWwindow =
		glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_GLFWwindow) {
		std::cerr << "Couldn't create glfw window." << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwSetKeyCallback(m_GLFWwindow, key_callback);
	glfwSetMouseButtonCallback(m_GLFWwindow, mouse_button_callback);
	glfwSetCursorPosCallback(m_GLFWwindow, cursor_position_callback);
	glfwSetWindowSizeCallback(m_GLFWwindow, window_resize_callback);

	GlobalGLFWEventHandler::GetEventPoll()[m_GLFWwindow].windowGLFW = this;

	GlobalGLFWEventHandler::GetEventPoll()[m_GLFWwindow]
		.windowGLFW->SetEventHandler(eventHandler);

	glfwMakeContextCurrent(m_GLFWwindow);
	glfwSwapInterval(1);
}

WindowGLFW::~WindowGLFW() {
	glfwDestroyWindow(m_GLFWwindow);
	glfwTerminate();
}

bool WindowGLFW::ShouldClose() const {
	return glfwWindowShouldClose(m_GLFWwindow);
}

void WindowGLFW::SwapBuffers() const { glfwSwapBuffers(m_GLFWwindow); }

void WindowGLFW::PollEvents() const {
	glfwPollEvents();
	GlobalGLFWEventHandler::PollEvents(m_GLFWwindow);
}

} // namespace renderel
