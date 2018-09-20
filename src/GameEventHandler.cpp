#include "GameEventHandler.hpp"

#define MOUSE_OFFSET 1024

namespace renderel {

// FIXME: pressing keys stops mouse from moving WHY???
void GameEventHandler::OnKeyDown(uint32 keyCode, bool isRepeat) {
	updateInput(keyCode, 1.0f, isRepeat);
}

void GameEventHandler::OnKeyUp(uint32 keyCode, bool isRepeat) {
	updateInput(keyCode, -1.0f, isRepeat);
}

void GameEventHandler::OnMouseDown(uint32 mouseButton,
								   unsigned char numClicks) {
	updateInput(mouseButton + MOUSE_OFFSET, 1.0f, false);
}

void GameEventHandler::OnMouseUp(uint32 mouseButton, unsigned char numClicks) {
	updateInput(mouseButton + MOUSE_OFFSET, -1.0f, false);
}

void GameEventHandler::OnMouseMove(int32 mousePosX, int32 mousePosY) {
	m_MousePosition.x = mousePosX;
	m_MousePosition.y = mousePosY;
}

void GameEventHandler::AddKeyControl(uint32 keyCode, InputControl &inputControl,
									 float weight) {
	m_Inputs[keyCode].push_back(InputPart(weight, inputControl));
}

void GameEventHandler::AddMouseControl(uint32 mouseButton,
									   InputControl &inputControl,
									   float weight) {
	m_Inputs[mouseButton + MOUSE_OFFSET].push_back(
		InputPart(weight, inputControl));
}

void GameEventHandler::updateInput(uint32 inputCode, float direction,
								   bool isRepeat) {
	if (isRepeat) {
		return;
	}

	for (auto &input : m_Inputs[inputCode]) {
		input.inputControl.AddAmount(input.weight * direction);
	}
}

} // namespace renderel
