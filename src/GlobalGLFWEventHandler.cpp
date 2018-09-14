#include "GlobalGLFWEventHandler.hpp"

namespace renderel {

std::unordered_map<GLFWwindow *, WindowEventData>
	GlobalGLFWEventHandler::m_EventPoll;

void GlobalGLFWEventHandler::PollEvents(GLFWwindow *window) {
	auto &windowEventData = m_EventPoll[window];
	HandleEvents(windowEventData);
}

void GlobalGLFWEventHandler::PushEvent(GLFWwindow *window, const Event &event) {
	m_EventPoll[window].events.push(event);
}

void GlobalGLFWEventHandler::HandleKeyEvent(EventHandler *handler,
											const Event &event) {
	switch (event.keyEvent.action) {
	case PRESS:
		handler->OnKeyDown(event.keyEvent.key, false);
		break;
	case KEYUP:
		handler->OnKeyUp(event.keyEvent.key, false);
		break;
	case KEYREPEAT:
		handler->OnKeyDown(event.keyEvent.key, true);
		break;
	}
}

void GlobalGLFWEventHandler::HandleEvents(WindowEventData &windowEventData) {
	EventHandler *handler = windowEventData.eventHandler;
	std::queue<Event> &queue = windowEventData.events;

	unsigned char numRightDownClicks = 0;
	unsigned char numRightUpClicks = 0;
	unsigned char numLeftDownClicks = 0;
	unsigned char numLeftUpClicks = 0;

	while (!queue.empty()) {
		Event &event = queue.front();
		switch (event.type) {
		case KEY:
			HandleKeyEvent(handler, event);
			break;

		case MOUSEBUTTON:
			switch (event.mouseButtonEvent.action) {
			case PRESS:
				if (event.mouseButtonEvent.button == MOUSE_BUTTON_LEFT) {
					++numLeftDownClicks;
				} else {
					++numRightDownClicks;
				}
				break;

			case KEYUP:
				if (event.mouseButtonEvent.button == MOUSE_BUTTON_LEFT) {
					++numLeftUpClicks;
				} else {
					++numRightUpClicks;
				}
				break;
			}
			break;

		case MOUSEMOTION:
			handler->OnMouseMove(event.mouseMotionEvent.xPos,
								 event.mouseMotionEvent.yPos);
			break;
		}

		queue.pop();
	}

	if (numLeftDownClicks > 0) {
		handler->OnMouseDown(MOUSE_BUTTON_LEFT, numLeftDownClicks);
	}
	if (numLeftUpClicks > 0) {
		handler->OnMouseUp(MOUSE_BUTTON_LEFT, numLeftUpClicks);
	}
	if (numRightDownClicks > 0) {
		handler->OnMouseDown(MOUSE_BUTTON_RIGHT, numRightDownClicks);
	}
	if (numRightUpClicks > 0) {
		handler->OnMouseUp(MOUSE_BUTTON_RIGHT, numRightUpClicks);
	}
}

} // namespace renderel
