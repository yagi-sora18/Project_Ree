#include "InGame.h"
#include <cstring>
#include "../Map/MapLoader.h"
#include "../Utillity/InputControl.h"
#include "Result.h"
#include "SceneManager.h"
#include "../Object/ObjectManager.h"
#include "../Object/Item/Coin.h"
#include "DxLib.h"

// 画面レイアウト情報
namespace {
    constexpr int SCREEN_W = 1300;
    constexpr int SCREEN_H = 800;
    constexpr int UI_WIDTH = 250;                 // 左のUIレーン幅
    constexpr int GAME_W = SCREEN_W - UI_WIDTH; // 右のゲーム領域
    constexpr int GAME_OFF_X = UI_WIDTH;            // ゲーム描画のXオフセット
}

// ==== Keyboard Help (A / D / SPACE) ==============================
static void DrawKeycap(int x, int y, int w, const char* label, bool on) {
    int bg = on ? GetColor(70, 160, 255) : GetColor(40, 45, 55);
    int fg = on ? GetColor(255, 255, 255) : GetColor(200, 205, 215);
    DrawBox(x, y, x + w, y + 32, bg, TRUE);
    DrawBox(x, y, x + w, y + 32, GetColor(90, 90, 110), FALSE);
    int tx = x + (w - (int)strlen(label) * 8) / 2;
    int ty = y + 8;
    DrawString(tx, ty, label, fg);
}

static void DrawKeyHelp(int baseX, int baseY, int width) {
    // タイトル
    DrawString(baseX, baseY, "KEYS", GetColor(230, 230, 240));

    // 枠
    int bx = baseX, by = baseY + 20, bw = width, bh = 88;
    DrawBox(bx, by, bx + bw, by + bh, GetColor(28, 30, 38), TRUE);
    DrawBox(bx, by, bx + bw, by + bh, GetColor(90, 90, 110), FALSE);

    // キー状態（DxLib）
    bool kA = (CheckHitKey(KEY_INPUT_A) != 0);
    bool kD = (CheckHitKey(KEY_INPUT_D) != 0);
    bool kSPACE = (CheckHitKey(KEY_INPUT_SPACE) != 0);

    // 上段：キーキャップ
    int x = bx + 10, y = by + 10;
    DrawKeycap(x, y, 36, "A", kA);     // 左移動
    DrawKeycap(x + 46, y, 36, "D", kD);     // 右移動
    DrawKeycap(x + 92, y, 72, "SPACE", kSPACE); // ジャンプ

    // 下段：説明
    int infoX = bx + 10, infoY = by + 50;
    int c = GetColor(200, 205, 215);
    DrawString(infoX, infoY, "A : 左移動", c);
    DrawString(infoX + 110, infoY, "D : 右移動", c);
    DrawString(infoX + 210, infoY, "SPACE : ジャンプ", c);
}

// ==== 左UI（キーボードのみ） ====================================
static void DrawLeftUI(int score) {
    // 左UIの背景帯
    DrawBox(0, 0, UI_WIDTH, SCREEN_H, GetColor(28, 30, 38), TRUE);
    // 右縁ライン
    DrawBox(UI_WIDTH - 1, 0, UI_WIDTH, SCREEN_H, GetColor(90, 90, 110), TRUE);

    int uiX = 16, uiY = 16;

    // スコア表示
    DrawFormatString(uiX, uiY, GetColor(230, 230, 240), "SCORE : %d", score);
    uiY += 28;

    // キーボードヘルプ（A / D / SPACE のみ）
    DrawKeyHelp(uiX, uiY, UI_WIDTH - 32);
    uiY += 20 + 88 + 16;
}

// =================================================================

InGame::InGame() : player(nullptr), now_scene(eSceneType::eInGame), camera_y(0) {}
InGame::~InGame() {}

void InGame::Initialize()
{
    player = new Player();
    object_manager.Add(player);

    // マップ読み込み（Platform / Coin / Wall）
    std::vector<Platform> temp_platforms;
    std::vector<Coin>     temp_coins;
    std::vector<Wall>     temp_wall;
    LoadMapFromCSV("Resource/Map/map01.csv", temp_platforms, temp_coins, temp_wall);

    for (auto& p : temp_platforms) {
        object_manager.Add(new Platform(p.pos.x, p.pos.y, p.width, p.height));
    }
    for (auto& c : temp_coins) {
        object_manager.Add(new Coin(c.pos.x, c.pos.y));
    }
    for (auto& w : temp_wall) {
        // 壁も Platform として描画／当たり判定（必要なら Wall クラス側に差し替え）
        object_manager.Add(new Platform(w.pos.x, w.pos.y, w.width, w.height));
    }

    camera_y = 0;
}

eSceneType InGame::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

    // Enterでリザルトへ
    if (input->GetKeyDown(KEY_INPUT_RETURN)) {
        next_scene = eSceneType::eResult;
        return next_scene;
    }

    // プレイヤー更新
    player->Update(delta_second);

    // Platform抽出
    std::vector<Object*> platforms;
    for (auto* obj : object_manager.GetObjects()) {
        if (dynamic_cast<Platform*>(obj)) {
            platforms.push_back(obj);
        }
    }

    // コイン取得
    for (auto* obj : object_manager.GetObjects()) {
        auto* coin = dynamic_cast<Coin*>(obj);
        if (!coin || coin->collected) continue;

        // 距離での簡易判定
        float dx = (player->pos.x + 25) - coin->pos.x;
        float dy = (player->pos.y + 25) - coin->pos.y;
        float dist2 = dx * dx + dy * dy;
        if (dist2 < (35 * 35)) {
            coin->collected = true;
            object_manager.AddScore(10);
        }

        // 当たり判定（Collisionがある場合）
        if (IsCheckCollision(player->collision, coin->collision)) {
            coin->collected = true;
            object_manager.AddScore(10);
        }
    }

    // 物理
    player->ApplyPhysics(platforms);

    // カメラ（縦方向追従）
    camera_y = static_cast<int>(player->pos.y) - (SCREEN_H / 2);
    if (camera_y < 0) camera_y = 0;

    // 全オブジェクト更新
    object_manager.UpdateAll(delta_second);

    return now_scene;
}

void InGame::Draw()
{
    // 右のゲーム領域を塗る（任意）
    DrawBox(UI_WIDTH, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);

    // ゲーム描画（内部で GAME_OFF_X を使っていないなら、各描画側で +UI_WIDTH を加える設計に）
    object_manager.DrawAll(camera_y);

    // 左UI（キーボードのみ）
    DrawLeftUI(object_manager.GetScore());
}

void InGame::Finalize()
{
    object_manager.ClearAll();
}

eSceneType InGame::GetNowSceneType() const
{
    return now_scene;
}
