#pragma once
#include "../../Utillity/Vector2D.h"
#include "../../Utillity/Collision.h"

#include "../Object.h"
#include <vector>

class Player : public Object {
public:
    Vector2D vel;
    bool isJumping;
    bool isCharging;
    float chargePower;
    int width;
    int height;
    Collision collision;

    // �f�t�H���g�R���X�g���N�^�i�錾�j
    Player();

    // CSV������n�����( x, y, w, h )�Ő��������R���X�g���N�^
    Player(float x, float y, int w, int h);

    // �����o�֐�
    void Update(float delta_time) override;
    void ApplyPhysics(const std::vector<Object*>& platforms);
    void UpdateCollision();
    void Draw(int camera_y) const override;
};
