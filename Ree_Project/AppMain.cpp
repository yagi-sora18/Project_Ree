#include "DxLib.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ��ʐݒ�
    ChangeWindowMode(TRUE);
    SetGraphMode(640, 480, 32);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    // �Q�[�����[�v
    while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        // ���݂̃V�[�����X�V�E�`��
        SceneManager::GetInstance()->Update();
        SceneManager::GetInstance()->Draw();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
