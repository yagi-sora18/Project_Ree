#include "InGame.h"
#include "../Map/MapLoader.h"
#include "../Utillity/InputControl.h"
#include "Result.h"
#include "SceneManager.h"
#include "../Object/ObjectManager.h"
#include "DxLib.h"

InGame::InGame() : player(nullptr), now_scene(eSceneType::eInGame), camera_y(0) {}

InGame::~InGame() {}

void InGame::Initialize()
{
    player = new Player();
    object_manager.Add(player);

    // �ꎞ�I�� Platform / Coin ������vector�œǂݍ���
    std::vector<Platform> temp_platforms;
    std::vector<Coin> temp_coins;
    LoadMapFromCSV("Resource/Map/map01.csv", temp_platforms, temp_coins);

    for (auto& p : temp_platforms) {
        object_manager.Add(new Platform(p.pos.x, p.pos.y, p.width, p.height));
    }

    for (auto& c : temp_coins) {
        object_manager.Add(new Coin(c.pos.x, c.pos.y));
    }



    camera_y = 0;
}

eSceneType InGame::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

    // === Enter�L�[�����Ń��U���g�֑J�ځi�ǉ������j ===
    if (input->GetKeyDown(KEY_INPUT_RETURN)) {
        next_scene = eSceneType::eResult;
        return next_scene;
    }

    //�v���C���[�X�V
    player->Update(delta_second);

    // Platform�������o���ĕ�������
    std::vector<Object*> platforms;
    for (auto* obj : object_manager.GetObjects()) {
        if (dynamic_cast<Platform*>(obj)) {
            platforms.push_back(obj);
        }
    }

    // �S�I�u�W�F�N�g�X�V�O�ɃR�C���擾�`�F�b�N
    for (auto* obj : object_manager.GetObjects()) {
        auto* coin = dynamic_cast<Coin*>(obj);
        if (!coin || coin->collected) continue;

        // �v���C���[�ƃR�C���̊ȈՋ�������i���a15px�j
        float dx = player->pos.x - coin->pos.x;
        float dy = player->pos.y - coin->pos.y;
        float dist2 = dx * dx + dy * dy;
        if (dist2 < (15 * 15)) {
            coin->collected = true;
            object_manager.AddScore(10);
        }
    }


    player->ApplyPhysics(platforms);

    // �J�����Ǐ]
    camera_y = static_cast<int>(player->pos.y) - 240;
    if (camera_y < 0) camera_y = 0;

    // �S�I�u�W�F�N�g�X�V
    object_manager.UpdateAll(delta_second);

    //// �S�[�������i���FY�ʒu��100����ŃN���A�j
    //if (player->pos.y < 100) {
    //    now_scene = eSceneType::eResult;
    //}

    return now_scene;


}

void InGame::Draw()
{
    object_manager.DrawAll(camera_y);

    DrawFormatString(20, 20, GetColor(255, 255, 255),
        "SCORE: %d", object_manager.GetScore());
}




void InGame::Finalize()
{
    object_manager.ClearAll();
}

eSceneType InGame::GetNowSceneType() const
{
    return now_scene;
}
