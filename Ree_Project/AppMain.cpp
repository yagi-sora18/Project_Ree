#include "DxLib.h"
#include "Scene/SceneManager.h"
#include "Object/ObjectManager.h"

ObjectManager objectManager; // グローバル実体（必要なら残す）

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    if (DxLib_Init() == -1) return -1;

    // 144Hzなどに引っ張られないよう自前でfps制御
    SetWaitVSyncFlag(FALSE);
    SetDrawScreen(DX_SCREEN_BACK);

    // 最初のシーン
    SceneManager::GetInstance()->ChangeScene(eSceneType::eTitle);

    // 60fps固定用
    const int targetFPS = 60;
    const int frameMillis = 1000 / targetFPS;
    int prev = GetNowCount();

    while (ProcessMessage() == 0) {
        int frameStart = GetNowCount();

        // 経過時間(秒)を計算してUpdateに渡す
        float delta = (frameStart - prev) / 1000.0f;
        if (delta < 0.0f)  delta = 0.0f;   // 時計巻き戻り対策
        if (delta > 0.1f)  delta = 0.1f;   // 一時停止復帰の暴走防止(最大0.1s)
        prev = frameStart;

        // 更新＆描画
        if (SceneManager::GetInstance()->Update(delta)) break;

        ClearDrawScreen();
        SceneManager::GetInstance()->Draw();
        ScreenFlip();

        // 60fpsに固定
        int elapsed = GetNowCount() - frameStart;
        int wait = frameMillis - elapsed;
        if (wait > 0) WaitTimer(wait);     // Sleep(wait)でもOK
    }

    SceneManager::GetInstance()->Finalize();
    DxLib_End();
    return 0;
}
