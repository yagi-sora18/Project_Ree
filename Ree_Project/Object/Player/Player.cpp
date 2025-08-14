#include "Player.h"
#include "../../Utillity/InputControl.h"
#include "../../Object/Platform/Platform.h"
#include "../../Utillity/Collision.h"
#include "DxLib.h"

// --- 調整用パラメータ ---
static const float GRAVITY = 0.8f;
static const float MOVE_ACCEL_GROUND = 0.6f;  // 地上での加速
static const float MOVE_ACCEL_AIR = 0.3f;  // 空中での加速
static const float MAX_SPEED_X = 4.0f;  // 横最大速度
static const float GROUND_FRICTION = 0.80f; // 地上で入力が無いときの減速(乗算)
static const float AIR_DRAG = 0.98f; // 空中の抵抗(乗算)

static const float JUMP_POWER_MIN = 5.0f;
static const float JUMP_POWER_MAX = 20.0f;
static const float CHARGE_SPEED = 0.3f;

static const float PLAYER_W = 50.0f;
static const float PLAYER_H = 50.0f;

Player::Player()
{
    pos = Vector2D(300.0f, 1000.0f);
    vel = Vector2D(0.0f, 0.0f);
    isJumping = true;
    isCharging = false;
    chargePower = 0.0f;
    UpdateCollision();
}

void Player::Update(float delta_time)
{
    auto input = InputControl::GetInstance();

    // --- 横入力（地上/空中で加速度を変える） ---
    float ax = 0.0f;
    const bool left = input->GetKey(KEY_INPUT_A);
    const bool right = input->GetKey(KEY_INPUT_D);
    const float accel = isJumping ? MOVE_ACCEL_AIR : MOVE_ACCEL_GROUND;

    if (left)  ax -= accel;
    if (right) ax += accel;

    // 速度更新（空中でも継続して慣性が乗る）
    vel.x += ax;

    // 速度制限
    if (vel.x > MAX_SPEED_X) vel.x = MAX_SPEED_X;
    if (vel.x < -MAX_SPEED_X) vel.x = -MAX_SPEED_X;

    // 減速（地上は強め、空中は弱め）
    if (!left && !right) {
        if (isJumping) vel.x *= AIR_DRAG;
        else           vel.x *= GROUND_FRICTION;
    }

    // --- 溜めジャンプ（地上のみ） ---
    if (!isJumping) {
        if (input->GetKeyDown(KEY_INPUT_SPACE)) {
            isCharging = true;
            chargePower = JUMP_POWER_MIN;
        }
        if (isCharging && input->GetKey(KEY_INPUT_SPACE)) {
            chargePower += CHARGE_SPEED;
            if (chargePower > JUMP_POWER_MAX) chargePower = JUMP_POWER_MAX;
        }
        if (isCharging && input->GetKeyUp(KEY_INPUT_SPACE)) {
            isJumping = true;
            isCharging = false;
            vel.y = -chargePower; // 上向きへ初速度
        }
    }
}

void Player::ApplyPhysics(const std::vector<Object*>& objects)
{
    // --- まず横移動を反映（慣性が効く） ---
    pos.x += vel.x;
    UpdateCollision();

    // --- 「地上に立っているか」を確認 ---
    // 少しだけ下に押し当てて足場があるかを見る（1px）
    bool onGround = false;
    {
        float savedY = pos.y;
        pos.y += 1.0f;
        UpdateCollision();

        for (const auto& obj : objects) {
            auto* platform = dynamic_cast<Platform*>(obj);
            if (!platform) continue;
            if (IsCheckCollision(collision, platform->collision)) {
                onGround = true;
                break;
            }
        }
        // 元に戻す
        pos.y = savedY;
        UpdateCollision();
    }

    // 足場からはみ出していたら落下開始
    if (!onGround && !isJumping) {
        isJumping = true;
    }

    // --- 縦方向の物理 ---
    if (isJumping) {
        vel.y += GRAVITY;    // 重力加速度
        pos.y += vel.y;      // 位置更新
        UpdateCollision();

        // 足場と当たったら着地
        for (const auto& obj : objects) {
            auto* platform = dynamic_cast<Platform*>(obj);
            if (!platform) continue;

            if (IsCheckCollision(collision, platform->collision)) {
                if (vel.y >= 0.0f) { // 上昇中は無視、下降中のみ着地
                    pos.y = platform->pos.y - PLAYER_H; // 天面に揃える
                    vel.y = 0.0f;
                    isJumping = false;
                    UpdateCollision();
                }
                break;
            }
        }
    }
    else {
        // 地上にいる時は縦速度を常に0に保つ
        vel.y = 0.0f;
    }
}

void Player::UpdateCollision()
{
    collision.pivot = pos + Vector2D(PLAYER_W * 0.5f, PLAYER_H * 0.5f);
    collision.box_size = Vector2D(PLAYER_W, PLAYER_H);
    collision.point[0] = pos;
    collision.point[1] = pos + Vector2D(PLAYER_W, PLAYER_H);
    collision.object_type = ePlayer;
}

void Player::Draw(int camera_y) const
{
    DrawBox((int)pos.x, (int)(pos.y - camera_y),
        (int)(pos.x + PLAYER_W), (int)(pos.y + PLAYER_H - camera_y),
        GetColor(255, 0, 0), TRUE);

    if (isCharging) {
        int gaugeHeight = static_cast<int>((chargePower / JUMP_POWER_MAX) * 100);
        int color = GetColor(
            static_cast<int>((chargePower / JUMP_POWER_MAX) * 255),
            static_cast<int>((1.0f - chargePower / JUMP_POWER_MAX) * 255),
            0
        );
        int gaugeX = static_cast<int>(pos.x - 10);
        int gaugeY = static_cast<int>(pos.y - gaugeHeight - 10 - camera_y);

        DrawBox(gaugeX, gaugeY,
            gaugeX + 10, gaugeY + gaugeHeight,
            color, TRUE);
    }
}
