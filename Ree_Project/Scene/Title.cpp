#include "Title.h"
#include <DxLib.h>
#include "../Utillity/InputControl.h"


void Title::Update(float) {
	InputControl::GetInstance()->Update();
	if (InputControl::GetInstance()->GetKeyDown(KEY_INPUT_SPACE)) {
		const_cast<eSceneType&>(next) = eSceneType::eInGame;
	}
}


void Title::Draw() {
	DrawString(40, 40, "JumpKing-like Demo - Press SPACE", GetColor(255, 255, 255));
}