#include "DxLib.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // 画面設定
    ChangeWindowMode(TRUE);
    SetGraphMode(640, 480, 32);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    // ゲームループ
    while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        // 現在のシーンを更新・描画
        SceneManager::GetInstance()->Update();
        SceneManager::GetInstance()->Draw();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
