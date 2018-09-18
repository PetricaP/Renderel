#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "EventHandler.hpp"
#include <string>

namespace renderel {

class Window {
  protected:
	int m_Width;
	int m_Height;
	EventHandler *m_EventHandler = nullptr;

  protected:
	Window(int width, int height, EventHandler *eventHandler);

  public:
	virtual ~Window() = default;

	virtual bool ShouldClose() const = 0;
	virtual void SwapBuffers() const = 0;
	virtual void PollEvents() const = 0;
	virtual void *GetAPIHandle() const = 0;
	virtual void Close() const = 0;
	virtual void DisableMouse() const = 0;
	virtual void EnableMouse() const = 0;

	void SetWidth(int width) { m_Width = width; }
	void SetHeight(int height) { m_Height = height; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	EventHandler *GetEventHandler() const { return m_EventHandler; }
	void SetEventHandler(EventHandler *handler) { m_EventHandler = handler; }
};

} // namespace renderel

#endif // WINDOW_HPP
