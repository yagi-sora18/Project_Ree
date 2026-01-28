#include "Platform.h"
#include "../../Utillity/ResourceManager.h"
#include <DxLib.h>


//static constexpr float GAME_OFF_X = 250.0f; // ‹¤’Ê‰»„§


//void Platform::Draw(int camera_y) {
//	DrawBox((int)(pos.x - GAME_OFF_X), (int)(pos.y - camera_y),
//		(int)(pos.x + width - GAME_OFF_X), (int)(pos.y + height - camera_y),
//		GetColor(120, 120, 120), true);
//}


//void Platform::Draw(int camera_x, int camera_y) {
//	DrawBox((int)(pos.x - camera_x), (int)(pos.y - camera_y),
//		+(int)(pos.x + width - camera_x), (int)(pos.y + height - camera_y),
//		GetColor(120, 120, 120), true);
//}


//void Platform::Draw(int camera_x, int camera_y, int off_x, int off_y)
//{
//    DrawBox((int)(pos.x - camera_x + off_x), (int)(pos.y - camera_y + off_y),
//        (int)(pos.x + width - camera_x + off_x), (int)(pos.y + height - camera_y + off_y),
//
//        GetColor(120, 120, 120), true);
//}


void Platform::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
    static bool loaded = false;
    static int platformImage = -1;

    const int drawMargin = 25; //‘å‚«‚³•ÏX


    if (!loaded) {
        platformImage = ResourceManager::GetInstance()->LoadImage("Resource/Image/Ashiba.png");
        loaded = true;
    }

    int x0 = (int)(pos.x - camera_x + off_x) - drawMargin;
    int y0 = (int)(pos.y - camera_y + off_y) - drawMargin;
    int x1 = (int)(pos.x + width - camera_x + off_x) + drawMargin;
    int y1 = (int)(pos.y + height - camera_y + off_y) + drawMargin;

    if (platformImage < 0) {
        // “Ç‚Ýž‚ÝŽ¸”sŽž‚Ì•ÛŒ¯iŠDF‚Ì” j
        DrawBox(x0, y0, x1, y1, GetColor(120, 120, 120), TRUE);
        return;
    }

    // ‘«ê‚ð”ÍˆÍ‚É‡‚í‚¹‚Ä•`‰æ
    DrawExtendGraph(x0, y0, x1, y1, platformImage, TRUE);
}