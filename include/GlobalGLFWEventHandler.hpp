#ifndef GLOBALGLFWEVENTHANDLER_HPP
#define GLOBALGLFWEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <queue>
#include <unordered_map>

namespace renderel {

// TODO: Add codes for events and keys
enum Type {
    KEYUP = GLFW_RELEASE,
    KEYDOWN = GLFW_PRESS,
    KEYREPEAT = GLFW_REPEAT,
    MOUSEUP,
    MOUSEDOWN
};

struct Event {
	Type type;
	unsigned int key;
	unsigned int action;
};

struct WindowEventData {
    EventHandler *eventHandler;
    std::queue<Event> events;
};

class GlobalGLFWEventHandler {
  private:
    std::unordered_map<GLFWwindow *, WindowEventData> m_EventPoll;

  public:
	void PollEvents(GLFWwindow *window) {
        auto &windowEventData = m_EventPoll[window];
        EventHandler *handler = windowEventData.eventHandler;
        std::queue<Event> &queue = windowEventData.events;
        static int count = 0;
        while (!queue.empty()) {
			count++;
			Event &event = queue.front();
			switch (event.action) {
            case MOUSEDOWN:
				handler->OnMouseUp(event.key, false);
				break;
            case MOUSEUP:
				handler->OnMouseDown(event.key, false);
                break;
            case KEYDOWN:
                handler->OnKeyDown(event.key, false);
                break;
            case KEYUP:
                handler->OnKeyUp(event.key, false);
                break;
            case KEYREPEAT:
                handler->OnKeyDown(event.key, true);
                break;
            }
			queue.pop();
		}
	}

	void PushEvent(GLFWwindow *window, Event event) {
        m_EventPoll[window].events.push(event);
	}

    std::unordered_map<GLFWwindow *, WindowEventData> &GetEventPoll() {
        return m_EventPoll;
    }
};

} // namespace renderel

#endif // GLOBALGLFWEVENTHANDLER_HPP
