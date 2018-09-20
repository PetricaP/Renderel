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
	std::unordered_map<uint32, std::vector<InputPart>> m_Inputs;
	math::Vec2<int32> m_MousePosition;

  public:
	GameEventHandler() = default;

	void OnKeyDown(uint32 keyCode, bool isRepeat) override;
	void OnKeyUp(uint32 keyCode, bool isRepeat) override;
	void OnMouseDown(uint32 mouseButton, unsigned char numClicks) override;
	void OnMouseUp(uint32 mouseButton, unsigned char numClicks) override;
	void OnMouseMove(int32 mousePosX, int32 mousePosY) override;

	void AddKeyControl(uint32 keyCode, InputControl &inputControl,
					   float weight = 1.0f);
	void AddMouseControl(uint32 mouseButton, InputControl &inputControl,
						 float weight = 1.0f);

	math::Vec2<int32> GetMousePosition() const { return m_MousePosition; }

  private:
	void updateInput(uint32 inputCode, float direction, bool isRepeat);
};

} // namespace renderel

#endif // GAMEEVENTHANDLER_HPP
