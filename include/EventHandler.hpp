#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

namespace renderel {

class EventHandler {
  private:
  public:
    EventHandler() = default;
    virtual ~EventHandler() = default;

    virtual void OnKeyDown(unsigned int, bool) {}
    virtual void OnKeyUp(unsigned int, bool) {}
    virtual void OnMouseDown(unsigned int, unsigned char) {}
    virtual void OnMouseUp(unsigned int, unsigned char) {}
    virtual void OnMouseMove(int, int) {}
};

} // namespace renderel

#endif // EVENTHANDLER_HPP
