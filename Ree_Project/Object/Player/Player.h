#pragma once
#include <vector>          // �� ���ꂪ������ std::vector ����`�ɂȂ��Ă��܂���
#include <algorithm>
#include "../Object.h"

class Player : public Object {
public:
    Player(float x, float y, float w = 50.0f, float h = 50.0f);

    void Update(float dt) override;
    //void Draw(int camera_y) override;
    //void Draw(int camera_x, int camera_y) override;
    void Draw(int camera_x, int camera_y, int off_x, int off_y) override;

    // �� dt �t���̕����B�錾�ƒ�`����v������
    void ApplyPhysics(const std::vector<class Object*>& objects, float dt);

private:
    Vector2D vel{ 0,0 };
    bool isJumping{ false };

    // �`���[�W�W�����v
    bool  charging{ false };
    float charge_t{ 0.0f };
    static constexpr float CHARGE_MAX = 0.6f;
    static constexpr float JUMP_V0_MIN = 650.0f;
    static constexpr float JUMP_V0_MAX = 1700.0f;

    // �ړ�/����
    static constexpr float A_GROUND = 2800.0f;
    static constexpr float A_AIR = 600.0f;
    static constexpr float FRICTION_GROUND = 1800.0f;
    static constexpr float FRICTION_AIR = 300.0f;
    static constexpr float GRAVITY = 3000.0f;
};
