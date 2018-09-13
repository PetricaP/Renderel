#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

namespace renderel {

class EventHandler {
  private:
  public:
    EventHandler() = default;
    virtual ~EventHandler() = default;

    virtual void OnKeyDown(unsigned int keyCode, bool isRepeat) = 0;
    virtual void OnKeyUp(unsigned int keyCode, bool isRepeat) = 0;
    virtual void OnMouseDown(unsigned int mouseButton,
                             unsigned char numCliks) = 0;
    virtual void OnMouseUp(unsigned int mouseButton,
                           unsigned char numCliks) = 0;
    virtual void OnMouseMove(int mousePosX, int mousePosY, int deltaX,
                             int deltaY) = 0;
};

} // namespace renderel

#endif // EVENTHANDLER_HPP
