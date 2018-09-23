#include "GlobalGLFWEventHandler.hpp"
#include "Debug.hpp"
#include "graphics/Renderer.hpp"

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

void GlobalGLFWEventHandler::HandleKeyEvent(WindowGLFW *window,
											const Event &event) {
	switch (event.keyEvent.action) {
	case PRESS:
		if (event.keyEvent.key == GLFW_KEY_F11) {
			window->ToggleFullScreen();
		} else {
			window->GetEventHandler()->OnKeyDown(event.keyEvent.key, false);
		}
		break;
	case KEYUP:
		window->GetEventHandler()->OnKeyUp(event.keyEvent.key, false);
		break;
	case KEYREPEAT:
		window->GetEventHandler()->OnKeyDown(event.keyEvent.key, true);
		break;
	}
}

void GlobalGLFWEventHandler::HandleEvents(WindowEventData &windowEventData) {
	EventHandler *handler = windowEventData.windowGLFW->GetEventHandler();
	std::queue<Event> &queue = windowEventData.events;

	unsigned char numRightDownClicks = 0;
	unsigned char numRightUpClicks = 0;
	unsigned char numLeftDownClicks = 0;
	unsigned char numLeftUpClicks = 0;

	while (!queue.empty()) {
		Event &event = queue.front();
		switch (event.type) {
		case KEY:
			HandleKeyEvent(windowEventData.windowGLFW, event);
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
		case WINDOWRESIZE:
			windowEventData.windowGLFW->SetWidth(event.windowEvent.width);
			windowEventData.windowGLFW->SetHeight(event.windowEvent.height);
			graphics::Renderer<>::SetViewPort(0, 0, event.windowEvent.width,
											  event.windowEvent.height);
			glViewport(0, 0, event.windowEvent.width, event.windowEvent.height);
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
