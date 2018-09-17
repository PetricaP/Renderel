#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "EventHandler.hpp"
#include <string>

namespace renderel {

class Window {
  private:
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

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Width; }
	EventHandler *GetEventHandler() const { return m_EventHandler; }
};

} // namespace renderel

#endif // WINDOW_HPP
