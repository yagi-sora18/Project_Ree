#include "Platform.h"
#include <DxLib.h>


static constexpr float GAME_OFF_X = 250.0f; // ã§í âªêÑèß


//void Platform::Draw(int camera_y) {
//	DrawBox((int)(pos.x - GAME_OFF_X), (int)(pos.y - camera_y),
//		(int)(pos.x + width - GAME_OFF_X), (int)(pos.y + height - camera_y),
//		GetColor(120, 120, 120), true);
//}

void Platform::Draw(int camera_x, int camera_y) {
	DrawBox((int)(pos.x - camera_x), (int)(pos.y - camera_y),
		+(int)(pos.x + width - camera_x), (int)(pos.y + height - camera_y),
		GetColor(120, 120, 120), true);
}