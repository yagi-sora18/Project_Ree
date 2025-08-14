#include "DxLib.h"
#include "Scene/SceneManager.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    // 最初のシーンをタイトルに設定
    SceneManager::GetInstance()->ChangeScene(eSceneType::eTitle);

    while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        if (SceneManager::GetInstance()->Update(1.0f / 60.0f)) break;
        SceneManager::GetInstance()->Draw();
        ScreenFlip();
    }

    SceneManager::GetInstance()->Finalize();
    DxLib_End();
    return 0;
}
