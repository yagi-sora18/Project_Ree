#include "Result.h"
#include <DxLib.h>
#include "../Utillity/InputControl.h"


void Result::Update(float) {
	InputControl::GetInstance()->Update();
	if (InputControl::GetInstance()->GetKeyDown(KEY_INPUT_RETURN)) {
		const_cast<eSceneType&>(next) = eSceneType::eTitle;
	}
}


void Result::Draw() {
	DrawString(40, 40, "Result - Press ENTER to Title", GetColor(255, 255, 255));
}