#ifndef GLOBALGLFWEVENTHANDLER_HPP
#define GLOBALGLFWEVENTHANDLER_HPP

#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <queue>
#include <unordered_map>

namespace renderel {

// TODO: Add codes for events and keys
enum Action {
	KEYUP = GLFW_RELEASE,
	PRESS = GLFW_PRESS,
	KEYREPEAT = GLFW_REPEAT,
};

enum Type { KEY, MOUSEBUTTON, MOUSEMOTION, WINDOWRESIZE };

#define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_RIGHT

struct WindowResizeEvent {
	int32 width;
	int32 height;
};

struct KeyboardEvent {
	uint32 key;
	uint32 action;
};

struct MouseButtonEvent {
	uint32 button;
	uint32 action;
};

struct MouseMotionEvent {
	int32 xPos;
	int32 yPos;
};

struct Event {
	Type type;
	union {
		KeyboardEvent keyEvent;
		MouseButtonEvent mouseButtonEvent;
		MouseMotionEvent mouseMotionEvent;
		WindowResizeEvent windowEvent;
	};
};

struct WindowEventData {
	WindowGLFW *windowGLFW;
	std::queue<Event> events;
};

class GlobalGLFWEventHandler {
  private:
	static std::unordered_map<GLFWwindow *, WindowEventData> m_EventPoll;

  public:
	static void PollEvents(GLFWwindow *window);
	static void PushEvent(GLFWwindow *window, const Event &event);

	static auto &GetEventPoll() { return m_EventPoll; }

  private:
	static void HandleEvents(WindowEventData &windowEventData);
	static void HandleKeyEvent(WindowGLFW *window, const Event &event);
	static void HandleFullScreen(WindowGLFW *window);
};

} // namespace renderel

#endif // GLOBALGLFWEVENTHANDLER_HPP
