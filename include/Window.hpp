#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "EventHandler.hpp"
#include <string>

namespace renderel {

class Window {
  protected:
	int32 m_Width;
	int32 m_Height;
	EventHandler *m_EventHandler = nullptr;

  protected:
	Window(int32 width, int32 height, EventHandler *eventHandler);

  public:
	virtual ~Window() = default;

	virtual bool ShouldClose() const = 0;
	virtual void SwapBuffers() const = 0;
	virtual void PollEvents() const = 0;
	virtual void *GetAPIHandle() const = 0;
	virtual void Close() const = 0;
	virtual void DisableMouse() const = 0;
	virtual void EnableMouse() const = 0;

	void SetWidth(int32 width) { m_Width = width; }
	void SetHeight(int32 height) { m_Height = height; }
	int32 GetWidth() const { return m_Width; }
	int32 GetHeight() const { return m_Height; }
	EventHandler *GetEventHandler() const { return m_EventHandler; }
	void SetEventHandler(EventHandler *handler) { m_EventHandler = handler; }
};

} // namespace renderel

#endif // WINDOW_HPP
