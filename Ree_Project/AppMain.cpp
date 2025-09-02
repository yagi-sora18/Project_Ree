#include "DxLib.h"
#include "Scene/SceneManager.h"
#include "Object/ObjectManager.h"

ObjectManager objectManager; // �O���[�o�����́i�K�v�Ȃ�c���j

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    if (DxLib_Init() == -1) return -1;

    // 144Hz�ȂǂɈ��������Ȃ��悤���O��fps����
    SetWaitVSyncFlag(FALSE);
    SetDrawScreen(DX_SCREEN_BACK);

    // �ŏ��̃V�[��
    SceneManager::GetInstance()->ChangeScene(eSceneType::eTitle);

    // 60fps�Œ�p
    const int targetFPS = 60;
    const int frameMillis = 1000 / targetFPS;
    int prev = GetNowCount();

    while (ProcessMessage() == 0) {
        int frameStart = GetNowCount();

        // �o�ߎ���(�b)���v�Z����Update�ɓn��
        float delta = (frameStart - prev) / 1000.0f;
        if (delta < 0.0f)  delta = 0.0f;   // ���v�����߂�΍�
        if (delta > 0.1f)  delta = 0.1f;   // �ꎞ��~���A�̖\���h�~(�ő�0.1s)
        prev = frameStart;

        // �X�V���`��
        if (SceneManager::GetInstance()->Update(delta)) break;

        ClearDrawScreen();
        SceneManager::GetInstance()->Draw();
        ScreenFlip();

        // 60fps�ɌŒ�
        int elapsed = GetNowCount() - frameStart;
        int wait = frameMillis - elapsed;
        if (wait > 0) WaitTimer(wait);     // Sleep(wait)�ł�OK
    }

    SceneManager::GetInstance()->Finalize();
    DxLib_End();
    return 0;
}
