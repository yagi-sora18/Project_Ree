#include "InGame.h"
#include "../Map/MapLoader.h"
#include "../Utillity/InputControl.h"
#include "Result.h"
#include "SceneManager.h"
#include "DxLib.h"

InGame::InGame()
{
    // プレイヤーとマップの初期化
    LoadMapFromCSV("Resource/Map/map01.csv", platforms, coins);
    player = Player();
    camera_y = 0;
}

InGame::~InGame()
{
    // 現時点で特に破棄するリソースはなし
}

void InGame::Update()
{
    InputControl::GetInstance()->Update();

    player.Update();
    player.ApplyPhysics(platforms);

    // カメラ追従処理
    camera_y = static_cast<int>(player.pos.y) - 240; // SCREEN_HEIGHT / 2
    if (camera_y < 0) camera_y = 0;

    // ゲームクリア判定（例：プレイヤーが最上部に到達）
    if (player.pos.y < 100) {
        SceneManager::GetInstance()->ChangeScene(new Result());
    }
}

void InGame::Draw()
{
    // 描画順：足場 → コイン → プレイヤー
    for (auto& p : platforms) p.Draw(camera_y);
    for (auto& c : coins) c.Draw(camera_y);
    player.Draw(camera_y);
}
