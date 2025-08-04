#include "DxLib.h"
#include "Utillity/InputControl.h"
#include "Object/Player/Player.h"
#include "Object/Platform/Platform.h"
#include "Object/Item/Coin.h"

#include "Map/MapLoader.h"



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    Player player;

    std::vector<Platform> platforms;
    std::vector<Coin> coins;

    LoadMapFromCSV("Resource/Map/map01.csv", platforms, coins);

    int camera_y = 0;

    while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        InputControl::GetInstance()->Update();
        player.Update();
        player.ApplyPhysics(platforms);

        // カメラY追従（上下）
        camera_y = static_cast<int>(player.pos.y) - SCREEN_HEIGHT / 2;
        if (camera_y < 0) camera_y = 0;


        // 地面描画

        for (auto& p : platforms) p.Draw(camera_y);
        for (auto& c : coins) c.Draw(camera_y);

        player.Draw(camera_y);

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
