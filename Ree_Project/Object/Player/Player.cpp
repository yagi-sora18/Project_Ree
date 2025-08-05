#include "Player.h"
#include "../../Utillity/InputControl.h"
#include "../../Object/Platform/Platform.h"
#include "../../Utillity/Collision.h"
#include "DxLib.h"

const float GRAVITY = 0.5f;
const float JUMP_POWER_MIN = 5.0f;
const float JUMP_POWER_MAX = 20.0f;
const float CHARGE_SPEED = 0.3f;
const float MOVE_SPEED = 2.0f;

Player::Player()
{
    pos = Vector2D(300.0f, 1000.0f);
    vel = Vector2D(0.0f, 0.0f);
    isJumping = true;
    isCharging = false;
    chargePower = 0.0f;
    UpdateCollision();
}

void Player::Update()
{
    auto input = InputControl::GetInstance();

    // ←→ 移動（地上・空中問わず）
    if (input->GetKey(KEY_INPUT_A)) pos.x -= MOVE_SPEED;
    if (input->GetKey(KEY_INPUT_D)) pos.x += MOVE_SPEED;

    // 地上でのみジャンプ受付
    if (!isJumping)
    {
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
            vel.y = -chargePower;
        }
    }
}

void Player::ApplyPhysics(const std::vector<Platform>& platforms)
{
    // X軸の移動（ステップ分割）
    const int stepCount = 10;
    float stepX = vel.x / stepCount;
    bool xBlocked = false;

for (int i = 0; i < stepCount; ++i)
{
    pos.x += stepX;
    UpdateCollision();

    for (const auto& platform : platforms)
    {
        if (IsCheckCollision(collision, platform.collision))
        {
            pos.x -= stepX;
            xBlocked = true;
            UpdateCollision();
            break;
        }
    }

    if (xBlocked) break;
}

// 衝突したときだけ vel.x を 0 にリセット（次のフレームで入力再適用）
if (xBlocked) {
    vel.x = 0.0f;
}


    // Y軸の重力適用
    vel.y += GRAVITY;
    float stepY = vel.y / stepCount;

    for (int i = 0; i < stepCount; ++i)
    {
        pos.y += stepY;
        UpdateCollision();

        for (const auto& platform : platforms)
        {
            // 上昇中はすり抜け、落下中は着地判定
            if (vel.y > 0.0f && IsCheckCollision(collision, platform.collision))
            {
                pos.y = platform.pos.y - 50;
                vel.y = 0.0f;
                isJumping = false;
                UpdateCollision();
                return;
            }
        }
    }
}


void Player::UpdateCollision()
{
    collision.pivot = pos + Vector2D(25, 25);
    collision.box_size = Vector2D(50, 50);
    collision.point[0] = pos;
    collision.point[1] = pos + Vector2D(50, 50);
    collision.object_type = ePlayer;
}

void Player::Draw(int camera_y) const
{
    DrawBox((int)pos.x, (int)(pos.y - camera_y), (int)(pos.x + 50), (int)(pos.y + 50 - camera_y), GetColor(255, 0, 0), TRUE);

    if (isCharging) {
        int gaugeWidth = static_cast<int>((chargePower / JUMP_POWER_MAX) * 100);
        int color = GetColor(
            static_cast<int>((chargePower / JUMP_POWER_MAX) * 255),
            static_cast<int>((1.0f - chargePower / JUMP_POWER_MAX) * 255),
            0
        );
        DrawBox(10, 10, 10 + gaugeWidth, 30, color, TRUE);
    }
}
