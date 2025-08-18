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

    // 一時的に Platform / Coin を仮のvectorで読み込む
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

    // === Enterキー押下でリザルトへ遷移（追加処理） ===
    if (input->GetKeyDown(KEY_INPUT_RETURN)) {
        next_scene = eSceneType::eResult;
        return next_scene;
    }

    //プレイヤー更新
    player->Update(delta_second);

    // Platformだけ抽出して物理処理
    std::vector<Object*> platforms;
    for (auto* obj : object_manager.GetObjects()) {
        if (dynamic_cast<Platform*>(obj)) {
            platforms.push_back(obj);
        }
    }

    // 全オブジェクト更新前にコイン取得チェック
    for (auto* obj : object_manager.GetObjects()) {
        auto* coin = dynamic_cast<Coin*>(obj);
        if (!coin || coin->collected) continue;

        // プレイヤーとコインの簡易距離判定（半径15px）
        float dx = player->pos.x - coin->pos.x;
        float dy = player->pos.y - coin->pos.y;
        float dist2 = dx * dx + dy * dy;
        if (dist2 < (15 * 15)) {
            coin->collected = true;
            object_manager.AddScore(10);
        }
    }


    player->ApplyPhysics(platforms);

    // カメラ追従
    camera_y = static_cast<int>(player->pos.y) - 240;
    if (camera_y < 0) camera_y = 0;

    // 全オブジェクト更新
    object_manager.UpdateAll(delta_second);

    //// ゴール処理（仮：Y位置が100より上でクリア）
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
