#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include "Input.hpp"
#include "core/Common.hpp"

namespace renderel {

class EventHandler {
  private:
  public:
	EventHandler() = default;
	virtual ~EventHandler() = default;

	virtual void OnKeyDown(uint32, bool) {}
	virtual void OnKeyUp(uint32, bool) {}
	virtual void OnMouseDown(uint32, unsigned char) {}
	virtual void OnMouseUp(uint32, unsigned char) {}
	virtual void OnMouseMove(int32, int32) {}
};

} // namespace renderel

#endif // EVENTHANDLER_HPP
