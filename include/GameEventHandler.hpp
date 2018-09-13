#ifndef GAMEEVENTHANDLER_HPP
#define GAMEEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include <iostream>

namespace renderel {

class GameEventHandler final : public EventHandler {
  private:
  public:
    // TODO: Finish the input management system benny-style
    GameEventHandler() = default;
    void OnKeyDown(unsigned int keyCode, bool isRepeat) override {
        std::cout << "Key down: " << keyCode << " Repeat: " << isRepeat
                  << std::endl;
    }
    void OnKeyUp(unsigned int keyCode, bool isRepeat) override {
        std::cout << "Key up: " << keyCode << " Repeat: " << isRepeat
                  << std::endl;
    }
    void OnMouseDown(unsigned int mouseButton,
                     unsigned char numClicks) override {
        std::cout << "Mouse down: " << mouseButton
                  << " Num clicks: " << numClicks << std::endl;
    }
    void OnMouseUp(unsigned int mouseButton, unsigned char numClicks) override {
        std::cout << "Mouse up: " << mouseButton << " Num clicks: " << numClicks
                  << std::endl;
    }
    void OnMouseMove(int mousePosX, int mousePosY, int deltaX,
                     int deltaY) override {
        std::cout << "Mouse moved to: " << mousePosX << " " << mousePosY
                  << " Delta: " << deltaX << " " << deltaY << std::endl;
    }
};

} // namespace renderel

#endif // GAMEEVENTHANDLER_HPP
