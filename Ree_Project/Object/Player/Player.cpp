#include "Player.h"
#include "../../Utillity/InputControl.h"
#include "../../Object/Platform/Platform.h"
#include "../../Utillity/Collision.h"
#include "../../Object/Item/Coin.h"
#include "../ObjectManager.h"
#include "DxLib.h"

// --- �����p�p�����[�^ ---
static const float GRAVITY = 0.8f;
static const float MOVE_ACCEL_GROUND = 0.6f;  // �n��ł̉���
static const float MOVE_ACCEL_AIR = 0.3f;  // �󒆂ł̉���
static const float MAX_SPEED_X = 4.0f;  // ���ő呬�x
static const float GROUND_FRICTION = 0.80f; // �n��œ��͂������Ƃ��̌���(��Z)
static const float AIR_DRAG = 0.98f; // �󒆂̒�R(��Z)

static const float JUMP_POWER_MIN = 5.0f;
static const float JUMP_POWER_MAX = 20.0f;
static const float CHARGE_SPEED = 0.3f;

static const float PLAYER_W = 50.0f;
static const float PLAYER_H = 50.0f;

static const float GAME_OFF_X = 250.0f;

// ------------------- �R���X�g���N�^ -------------------

// �f�t�H���g�R���X�g���N�^�i�K����`����j
Player::Player()
{
   /* pos = Vector2D(300.0f, 1000.0f);
    vel = Vector2D(0.0f, 0.0f);
    isJumping = true;
    isCharging = false;
    chargePower = 0.0f;
    UpdateCollision();*/
}

// CSV ������^������ʒu�E�傫���ŏ���������R���X�g���N�^
Player::Player(float x, float y, int w, int h) : width(w), height(h)
{
    // float/int �̍��݂ɒ��ӁFpos �� float �����̂ł��̂܂ܑ��
    pos = Vector2D(x, y);
    vel = Vector2D(0.0f, 0.0f);
    isJumping = true;
    isCharging = false;
    chargePower = 0.0f;

    // ���� w,h ���g���ē����蔻��T�C�Y����ς���ꍇ�͂����Ŕ��f���Ă��������B
    // ���̎����͌Œ� PLAYER_W/PLAYER_H ���g���Ă���̂ŁA�K�v�ɉ����� UpdateCollision �𒲐����Ă��������B

    UpdateCollision();
}

// ------------------- ���\�b�h�{�� -------------------

void Player::Update(float delta_time)
{
    auto input = InputControl::GetInstance();

    // --- �R�C���擾���� ---
    {
        extern ObjectManager objectManager;
        for (auto* obj : objectManager.GetObjects()) {
            auto* coin = dynamic_cast<Coin*>(obj);
            if (!coin || coin->collected) continue;

            if (IsCheckCollision(collision, Collision{
                coin->pos + Vector2D(10, 10),
                Vector2D(20, 20),
                { coin->pos, coin->pos + Vector2D(20, 20) },
                eCastle
                })) {
                coin->collected = true;
                objectManager.AddScore(10);
            }
        }
    }

    // --- �����́i�n��/�󒆂ŉ����x��ς���j ---
    float ax = 0.0f;
    const bool left = input->GetKey(KEY_INPUT_A);
    const bool right = input->GetKey(KEY_INPUT_D);
    const float accel = isJumping ? MOVE_ACCEL_AIR : MOVE_ACCEL_GROUND;

    if (left)  ax -= accel;
    if (right) ax += accel;

    vel.x += ax;
    if (vel.x > MAX_SPEED_X) vel.x = MAX_SPEED_X;
    if (vel.x < -MAX_SPEED_X) vel.x = -MAX_SPEED_X;

    if (!left && !right) {
        if (isJumping) vel.x *= AIR_DRAG;
        else           vel.x *= GROUND_FRICTION;
    }

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
            vel.y = -chargePower;
        }
    }
}

void Player::ApplyPhysics(const std::vector<Object*>& objects)
{
    pos.x += vel.x;
    UpdateCollision();

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
        pos.y = savedY;
        UpdateCollision();
    }

    if (!onGround && !isJumping) {
        isJumping = true;
    }

    if (isJumping) {
        vel.y += GRAVITY;
        pos.y += vel.y;
        UpdateCollision();

        for (const auto& obj : objects) {
            auto* platform = dynamic_cast<Platform*>(obj);
            if (!platform) continue;

            if (IsCheckCollision(collision, platform->collision)) {
                if (vel.y >= 0.0f) {
                    pos.y = platform->pos.y - PLAYER_H;
                    vel.y = 0.0f;
                    isJumping = false;
                    UpdateCollision();
                }
                break;
            }
        }
    }
    else {
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
    DrawBox((int)(pos.x + GAME_OFF_X), (int)(pos.y - camera_y),
        (int)(pos.x + PLAYER_W + GAME_OFF_X), (int)(pos.y + PLAYER_H - camera_y),
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
