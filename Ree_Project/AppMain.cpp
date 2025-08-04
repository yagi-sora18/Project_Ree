#include "DxLib.h"
#include "Utillity/InputControl.h"
#include "Object/Player/Player.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GROUND_HEIGHT = 400;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    Player player;

    while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        InputControl::GetInstance()->Update();
        player.Update();

        // ’n–Ê•`‰æ
        DrawBox(0, GROUND_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(100, 255, 100), TRUE);

        player.Draw();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
