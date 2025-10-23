// �� Windows.h �� min/max �}�N���΍�BDxLib.h �̑O�ɓ����
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

static constexpr float GAME_OFF_X = 250.0f;

Player::Player(float x, float y, float w, float h)
    : Object(x, y, w, h) {
    collision.object_type = ePlayer;
}

void Player::Update(float dt) {
    auto in = InputControl::GetInstance();

    // ��������
    float ax = 0.0f;
    if (in->GetKey(KEY_INPUT_LEFT))  ax -= 1.0f;
    if (in->GetKey(KEY_INPUT_RIGHT)) ax += 1.0f;

    // �`���[�W�J�n/�ێ�/���
    if (!isJumping && in->GetKeyDown(KEY_INPUT_SPACE)) { charging = true; charge_t = 0.0f; }
    if (charging && in->GetKey(KEY_INPUT_SPACE)) { charge_t = (std::min)(charge_t + dt, CHARGE_MAX); } // �� (std::min) �Ń}�N���Փˉ��
    if (charging && in->GetKeyUp(KEY_INPUT_SPACE)) {
        float r = (CHARGE_MAX <= 0 ? 1.0f : (charge_t / CHARGE_MAX));
        float v0 = JUMP_V0_MIN + (JUMP_V0_MAX - JUMP_V0_MIN) * r;
        vel.y = -v0; isJumping = true; charging = false;
    }

    // ����/���C
    float a_move = (isJumping ? A_AIR : A_GROUND) * ax;
    vel.x += a_move * dt;

    float fr = (isJumping ? FRICTION_AIR : FRICTION_GROUND) * dt;
    if (ax == 0.0f) {
        if (vel.x > 0)      vel.x = (std::max)(0.0f, vel.x - fr);
        else if (vel.x < 0) vel.x = (std::min)(0.0f, vel.x + fr);
    }
}

void Player::ApplyPhysics(const std::vector<Object*>& objects, float dt) {
    // --- ���� ---
    float newX = pos.x + vel.x * dt;
    pos.x = newX; UpdateCollision();

    for (auto* obj : objects) {
        if (!obj || !obj->IsActive()) continue;
        if (obj->collision.object_type != eWall) continue; // ���ǂ̂�
        if (IsCheckCollision(collision, obj->collision)) {
            if (vel.x > 0) pos.x = obj->pos.x - width;           // �E���ɏՓ�
            else if (vel.x < 0) pos.x = obj->pos.x + obj->width; // �����ɏՓ�
            vel.x = 0; UpdateCollision();
        }
    }

    // --- ���� ---
    vel.y += GRAVITY * dt;
    float newY = pos.y + vel.y * dt;

    // �������̏�ʃX�C�[�v�iPlatform �̂ݒ��n�j
    if (vel.y > 0) {
        for (auto* obj : objects) {
            if (!obj || !obj->IsActive()) continue;
            if (obj->collision.object_type != ePlatform) continue;

            bool xOverlap = !(collision.point[1].x <= obj->collision.point[0].x ||
                collision.point[0].x >= obj->collision.point[1].x);
            float bottom0 = pos.y + height;
            float bottom1 = newY + height;
            float pfTop = obj->pos.y;

            if (xOverlap && bottom0 <= pfTop && bottom1 >= pfTop) {
                newY = pfTop - height;
                vel.y = 0;
                isJumping = false;
                break;
            }
        }
    }

    pos.y = newY; UpdateCollision();
}

//void Player::Draw(int camera_y) {
//    DrawBox((int)(pos.x - GAME_OFF_X), (int)(pos.y - camera_y),
//        (int)(pos.x + width - GAME_OFF_X), (int)(pos.y + height - camera_y),
//        GetColor(200, 50, 50), TRUE);
//}

//void Player::Draw(int camera_x, int camera_y)
//{
//    DrawBox((int)(pos.x - camera_x), (int)(pos.y - camera_y),
//        +(int)(pos.x + width - camera_x), (int)(pos.y + height - camera_y),
//        GetColor(200, 50, 50), TRUE);
//}

void Player::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
    DrawBox((int)(pos.x - camera_x + off_x), (int)(pos.y - camera_y + off_y),
    (int)(pos.x + width - camera_x + off_x), (int)(pos.y + height - camera_y + off_y),

    GetColor(200, 50, 50), TRUE);
}