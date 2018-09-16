#include "GameEventHandler.hpp"

#define MOUSE_OFFSET 1024

namespace renderel {

// FIXME: pressing keys stops mouse from moving WHY???
void GameEventHandler::OnKeyDown(unsigned int keyCode, bool isRepeat) {
	updateInput(keyCode, 1.0f, isRepeat);
}

void GameEventHandler::OnKeyUp(unsigned int keyCode, bool isRepeat) {
	updateInput(keyCode, -1.0f, isRepeat);
}

void GameEventHandler::OnMouseDown(unsigned int mouseButton,
								   unsigned char numClicks) {
	updateInput(mouseButton + MOUSE_OFFSET, 1.0f, false);
}

void GameEventHandler::OnMouseUp(unsigned int mouseButton,
								 unsigned char numClicks) {
	updateInput(mouseButton + MOUSE_OFFSET, -1.0f, false);
}

void GameEventHandler::OnMouseMove(int mousePosX, int mousePosY) {
	m_MousePosition.x = mousePosX;
	m_MousePosition.y = mousePosY;
}

void GameEventHandler::AddKeyControl(unsigned int keyCode,
									 InputControl &inputControl, float weight) {
	m_Inputs[keyCode].push_back(InputPart(weight, inputControl));
}

void GameEventHandler::AddMouseControl(unsigned int mouseButton,
									   InputControl &inputControl,
									   float weight) {
	m_Inputs[mouseButton + MOUSE_OFFSET].push_back(
		InputPart(weight, inputControl));
}

void GameEventHandler::updateInput(unsigned int inputCode, float direction,
								   bool isRepeat) {
	if (isRepeat) {
		return;
	}

	for (auto &input : m_Inputs[inputCode]) {
		input.inputControl.AddAmount(input.weight * direction);
	}
}

} // namespace renderel
