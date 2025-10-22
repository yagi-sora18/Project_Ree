#include <DxLib.h>
#include "Scene/SceneManager.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(1280, 720, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);


	SceneManager sm;
	unsigned int prev = GetNowCount();


	while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		unsigned int now = GetNowCount();
		float dt = (now - prev) / 1000.0f; // 秒
		prev = now;
		if (dt > 0.05f) dt = 0.05f; // セーフティ


		sm.Update(dt);
		sm.Draw();
		ScreenFlip();
	}


	DxLib_End();
	return 0;
}