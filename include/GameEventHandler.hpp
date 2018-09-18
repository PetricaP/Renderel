#ifndef GAMEEVENTHANDLER_HPP
#define GAMEEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include "InputControl.hpp"
#include "math/Vec2.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

namespace renderel {

struct InputPart {
	InputControl &inputControl;
	float weight;
	InputPart(float weight, InputControl &inputControl)
		: inputControl(inputControl), weight(weight) {}
};

class GameEventHandler final : public EventHandler {
  private:
	std::unordered_map<unsigned int, std::vector<InputPart>> m_Inputs;
	math::Vec2<int> m_MousePosition;

  public:
	GameEventHandler() = default;

	void OnKeyDown(unsigned int keyCode, bool isRepeat) override;
	void OnKeyUp(unsigned int keyCode, bool isRepeat) override;
	void OnMouseDown(unsigned int mouseButton,
					 unsigned char numClicks) override;
	void OnMouseUp(unsigned int mouseButton, unsigned char numClicks) override;
	void OnMouseMove(int mousePosX, int mousePosY) override;

	void AddKeyControl(unsigned int keyCode, InputControl &inputControl,
					   float weight = 1.0f);
	void AddMouseControl(unsigned int mouseButton, InputControl &inputControl,
						 float weight = 1.0f);

	math::Vec2<int> GetMousePosition() const { return m_MousePosition; }

  private:
	void updateInput(unsigned int inputCode, float direction, bool isRepeat);
};

} // namespace renderel

#endif // GAMEEVENTHANDLER_HPP
