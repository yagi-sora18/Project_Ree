#include "InGame.h"
#include "../Map/MapLoader.h"
#include "../Utillity/InputControl.h"
#include "Result.h"
#include "SceneManager.h"
#include "DxLib.h"

InGame::InGame()
{
    // �v���C���[�ƃ}�b�v�̏�����
    LoadMapFromCSV("Resource/Map/map01.csv", platforms, coins);
    player = Player();
    camera_y = 0;
}

InGame::~InGame()
{
    // �����_�œ��ɔj�����郊�\�[�X�͂Ȃ�
}

void InGame::Update()
{
    InputControl::GetInstance()->Update();

    player.Update();
    player.ApplyPhysics(platforms);

    // �J�����Ǐ]����
    camera_y = static_cast<int>(player.pos.y) - 240; // SCREEN_HEIGHT / 2
    if (camera_y < 0) camera_y = 0;

    // �Q�[���N���A����i��F�v���C���[���ŏ㕔�ɓ��B�j
    if (player.pos.y < 100) {
        SceneManager::GetInstance()->ChangeScene(new Result());
    }
}

void InGame::Draw()
{
    // �`�揇�F���� �� �R�C�� �� �v���C���[
    for (auto& p : platforms) p.Draw(camera_y);
    for (auto& c : coins) c.Draw(camera_y);
    player.Draw(camera_y);
}
