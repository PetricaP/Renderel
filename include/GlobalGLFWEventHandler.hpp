#ifndef GLOBALGLFWEVENTHANDLER_HPP
#define GLOBALGLFWEVENTHANDLER_HPP

#include "EventHandler.hpp"
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

enum Type { KEY, MOUSEBUTTON, MOUSEMOTION };

#define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_RIGHT

struct KeyboardEvent {
    unsigned int key;
    unsigned int action;
};

struct MouseButtonEvent {
    unsigned int button;
    unsigned int action;
};

struct MouseMotionEvent {
    int xPos;
    int yPos;
};

struct Event {
	Type type;
    union {
        KeyboardEvent keyEvent;
        MouseButtonEvent mouseButtonEvent;
        MouseMotionEvent mouseMotionEvent;
    };
};

struct WindowEventData {
    EventHandler *eventHandler;
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
    static void HandleKeyEvent(EventHandler *handler, const Event &event);
};

} // namespace renderel

#endif // GLOBALGLFWEVENTHANDLER_HPP
