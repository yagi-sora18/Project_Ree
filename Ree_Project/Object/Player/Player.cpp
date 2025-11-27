// ★ Windows.h の min/max マクロ対策。DxLib.h の前に入れる
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <algorithm>   // std::min / std::max
#include <vector>
#include <DxLib.h>

#include "../../Object/Player/Player.h"
#include "../../Utillity/InputControl.h"
#include "../../Object/Platform/Platform.h"
#include "../../Object/Wall/Wall.h"
#include "../../Utillity/Collision.h"
#include "../../Object/ObjectManager.h"
#include "../../Utillity/ResourceManager.h"

static constexpr float GAME_OFF_X = 250.0f;

Player::Player(float x, float y, float w, float h)
    : Object(x, y, w, h) {
    collision.object_type = ePlayer;
}

void Player::Update(float dt)
{
    auto in = InputControl::GetInstance();

    // 水平入力
    float ax = 0.0f;
    if (in->GetKey(KEY_INPUT_A))  ax -= 1.0f;
    if (in->GetKey(KEY_INPUT_D))  ax += 1.0f;

    // チャージ開始/維持/解放
    if (!isJumping && in->GetKeyDown(KEY_INPUT_SPACE)) {
        charging = true;
        charge_t = 0.0f;
    }
    if (charging && in->GetKey(KEY_INPUT_SPACE)) {
        charge_t = (std::min)(charge_t + dt, CHARGE_MAX); // (std::min) でマクロ衝突回避
    }
    if (charging && in->GetKeyUp(KEY_INPUT_SPACE)) {
        float r = (CHARGE_MAX <= 0 ? 1.0f : (charge_t / CHARGE_MAX));
        float v0 = JUMP_V0_MIN + (JUMP_V0_MAX - JUMP_V0_MIN) * r;
        vel.y = -v0;
        isJumping = true;
        charging = false;
    }

    // 加速/摩擦
    float a_move = (isJumping ? A_AIR : A_GROUND) * ax;
    vel.x += a_move * dt;

    float fr = (isJumping ? FRICTION_AIR : FRICTION_GROUND) * dt;
    if (ax == 0.0f) {
        if (vel.x > 0)      vel.x = (std::max)(0.0f, vel.x - fr);
        else if (vel.x < 0) vel.x = (std::min)(0.0f, vel.x + fr);
    }

    // ===== 着地タイマー更新 =====
    if (landingTimer > 0.0f) {
        landingTimer -= dt;
        if (landingTimer < 0.0f) landingTimer = 0.0f;
    }

    // ===== アニメ状態の決定 =====
    bool onGround = !isJumping;
    bool walking = onGround && std::fabs(vel.x) > 20.0f;

    if (!onGround) {
        // 空中にいるとき
        animeState = PlayerAnimeState::Jump;
    }
    else if (charging) {
        // 地上でチャージ中
        animeState = PlayerAnimeState::Charge;
    }
    else if (landingTimer > 0.0f) {
        // 着地直後
        animeState = PlayerAnimeState::Landing;
    }
    else if (walking) {
        // ある程度横に動いているなら歩き
        animeState = PlayerAnimeState::Walk;
    }
    else {
        // それ以外はアイドル
        animeState = PlayerAnimeState::Idle;
    }

    UpdateCollision();
}

void Player::ApplyPhysics(const std::vector<Object*>& objects, float dt)
{
    // --- 水平 ---
    float newX = pos.x + vel.x * dt;
    pos.x = newX;
    UpdateCollision();

    for (auto* obj : objects) {
        if (!obj || !obj->IsActive()) continue;
        if (obj->collision.object_type != eWall) continue; // 横壁のみ
        if (IsCheckCollision(collision, obj->collision)) {
            if (vel.x > 0)      pos.x = obj->pos.x - width;          // 右側に衝突
            else if (vel.x < 0) pos.x = obj->pos.x + obj->width;     // 左側に衝突
            vel.x = 0;
            UpdateCollision();
        }
    }

    // --- 垂直 ---
    vel.y += GRAVITY * dt;
    float newY = pos.y + vel.y * dt;

    // 落下時の上面スイープ（Platform のみ着地）
    if (vel.y > 0) {
        for (auto* obj : objects) {
            if (!obj || !obj->IsActive()) continue;
            if (obj->collision.object_type != ePlatform) continue;

            bool xOverlap =
                !(collision.point[1].x <= obj->collision.point[0].x ||
                    collision.point[0].x >= obj->collision.point[1].x);

            float bottom0 = pos.y + height;
            float bottom1 = newY + height;
            float pfTop = obj->pos.y;

            if (xOverlap && bottom0 <= pfTop && bottom1 >= pfTop) {
                // 着地
                newY = pfTop - height;
                vel.y = 0;

                // ジャンプ状態から地上に戻ったときだけ着地アニメ用タイマーをセット
                if (isJumping) {
                    landingTimer = 0.15f; // 0.15秒だけ Landing を表示
                }

                isJumping = false;
                break;
            }
        }
    }

    pos.y = newY;
    UpdateCollision();
}

void Player::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
    // ===== 画像のロード（最初に呼ばれたときだけ） =====
    static bool s_inited = false;
    static const std::vector<int>* sIdle = nullptr;
    static const std::vector<int>* sWalk = nullptr;
    static const std::vector<int>* sAct = nullptr; // Charge / Jump / Landing をまとめる

    if (!s_inited) {
        auto* rm = ResourceManager::GetInstance();

        sIdle = &rm->LoadAnimImages("player_idle", {
            "Resource/Image/Player_Idle_1.png"
            });

        sWalk = &rm->LoadAnimImages("player_walk", {
            "Resource/Image/Player_Walk_1.png",
            "Resource/Image/Player_Walk_2.png",
            "Resource/Image/Player_Walk_3.png",
            "Resource/Image/Player_Walk_4.png",
            "Resource/Image/Player_Walk_5.png",
            "Resource/Image/Player_Walk_6.png",
            "Resource/Image/Player_Walk_7.png"
            });

        // index 0: Charge, 1: Jump, 2: Landing
        sAct = &rm->LoadAnimImages("player_action", {
            "Resource/Image/Player_Gauge.png",
            "Resource/Image/Player_Jump.png",
            "Resource/Image/Player_Landing.png"
            });

        s_inited = true;
    }

    // ロードに失敗していた場合の保険
    auto safeGet = [](const std::vector<int>* vec, int index) -> int {
        if (!vec || vec->empty()) return 0;
        if (index < 0 || index >= (int)vec->size()) return 0;
        return (*vec)[index];
        };

    int handle = 0;

    // ===== 状態に応じて使うハンドルを決定 =====
    switch (animeState)
    {
    case PlayerAnimeState::Idle:
        handle = safeGet(sIdle, 0);
        break;

    case PlayerAnimeState::Walk:
    {
        const std::vector<int>* w = sWalk;
        if (w && !w->empty()) {
            int t = GetNowCount();
            int frame = (t / 120) % (int)w->size();   // 120msごとに次のコマ
            handle = safeGet(w, frame);
        }
    }
    break;

    case PlayerAnimeState::Charge:
        handle = safeGet(sAct, 0); // Player_Gauge.png
        break;

    case PlayerAnimeState::Jump:
        handle = safeGet(sAct, 1); // Player_Jump.png
        break;

    case PlayerAnimeState::Landing:
        handle = safeGet(sAct, 2); // Player_Landing.png
        break;
    }

    // もし handle が 0（画像なし）なら、今まで通りの四角形で描画
    if (handle == 0) {
        int x0 = (int)(pos.x - camera_x + off_x);
        int y0 = (int)(pos.y - camera_y + off_y);
        int x1 = (int)(pos.x + width - camera_x + off_x);
        int y1 = (int)(pos.y + height - camera_y + off_y);
        DrawBox(x0, y0, x1, y1, GetColor(0, 255, 0), TRUE);
        return;
    }

    // ===== 画像をプレイヤーの当たり判定サイズに合わせて描画 =====
    int x0 = (int)(pos.x - camera_x + off_x);
    int y0 = (int)(pos.y - camera_y + off_y);
    int x1 = (int)(pos.x + width - camera_x + off_x);
    int y1 = (int)(pos.y + height - camera_y + off_y);

    DrawExtendGraph(x0, y0, x1, y1, handle, TRUE);
}

float Player::GetChargeRatio() const
{
    if (!charging || CHARGE_MAX <= 0.0f) return 0.0f;

    float r = charge_t / CHARGE_MAX;
    return (r < 0.0f) ? 0.0f : (r > 1.0f ? 1.0f : r);
}
