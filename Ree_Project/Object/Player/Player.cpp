#include "Player.h"
#include "../../Utillity/InputControl.h"
#include "DxLib.h"

const int GROUND_HEIGHT = 400;
const float GRAVITY = 0.5f;
const float JUMP_POWER_MIN = 5.0f;
const float JUMP_POWER_MAX = 20.0f;
const float CHARGE_SPEED = 0.3f;
const float MOVE_SPEED = 2.0f;

Player::Player()
{
    pos = Vector2D(300.0f, GROUND_HEIGHT - 50.0f);
    vel = Vector2D(0.0f, 0.0f);
    isJumping = false;
    isCharging = false;
    chargePower = 0.0f;
}

void Player::Update()
{
    auto input = InputControl::GetInstance();

    // ‰¡ˆÚ“®
    if (input->GetKey(KEY_INPUT_A)) vel.x = -MOVE_SPEED;
    else if (input->GetKey(KEY_INPUT_D)) vel.x = MOVE_SPEED;
    else vel.x = 0.0f;

    if (!isJumping)
    {
        pos.x += vel.x;

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
    else
    {
        pos.x += vel.x;
        vel.y += GRAVITY;
        pos.y += vel.y;

        if (pos.y >= GROUND_HEIGHT - 50.0f) {
            pos.y = GROUND_HEIGHT - 50.0f;
            isJumping = false;
            vel.y = 0.0f;
            vel.x = 0.0f;
        }
    }
}

void Player::Draw() const
{
    DrawBox((int)pos.x, (int)pos.y, (int)(pos.x + 50), (int)(pos.y + 50), GetColor(255, 0, 0), TRUE);

    if (isCharging) {
        int gaugeWidth = static_cast<int>((chargePower / JUMP_POWER_MAX) * 100);
        DrawBox(10, 10, 10 + gaugeWidth, 30, GetColor(255, 255, 0), TRUE);
    }
}

