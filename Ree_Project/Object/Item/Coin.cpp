#include "Coin.h"
#include <DxLib.h>


static constexpr float GAME_OFF_X = 250.0f;


void Coin::Update(float) {
	// 毎フレーム同期（pivot/point/box）
	UpdateCollision();
}


//void Coin::Draw(int camera_y) 
void Coin::Draw(int camera_x, int camera_y) {
	if (collected) return;
	//int x = (int)(pos.x - GAME_OFF_X);
	int x = (int)(pos.x - camera_x);
	int y = (int)(pos.y - camera_y);
	DrawCircle(x + (int)width / 2, y + (int)height / 2, (int)(width / 2), GetColor(255, 215, 0), true);
}