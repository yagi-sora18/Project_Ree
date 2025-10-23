#include "Wall.h"
#include <DxLib.h>


static constexpr float GAME_OFF_X = 250.0f;


//void Wall::Draw(int camera_y) {
//	DrawBox((int)(pos.x - GAME_OFF_X), (int)(pos.y - camera_y),
//		(int)(pos.x + width - GAME_OFF_X), (int)(pos.y + height - camera_y),
//		GetColor(80, 80, 160), true);
//}

//void Wall::Draw(int camera_x, int camera_y) {
//	DrawBox((int)(pos.x - camera_x), (int)(pos.y - camera_y),
//		+(int)(pos.x + width - camera_x), (int)(pos.y + height - camera_y),
//		GetColor(80, 80, 160), true);
//}

void Wall::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
    DrawBox((int)(pos.x - camera_x + off_x), (int)(pos.y - camera_y + off_y),
        (int)(pos.x + width - camera_x + off_x), (int)(pos.y + height - camera_y + off_y),

        GetColor(80, 80, 160), true);
}