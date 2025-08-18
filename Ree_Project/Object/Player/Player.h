#pragma once
#include "../../Utillity/Vector2D.h"
#include "../../Utillity/Collision.h"

#include "../Object.h"
#include <vector>

class Platform;

class Player : public Object {
public:
    Vector2D vel;
    bool isJumping;
    bool isCharging;
    float chargePower;
    Collision collision;


    Player();
    void Update(float delta_time) override;
    void ApplyPhysics(const std::vector<Object*>& platforms);
    void UpdateCollision();
    void Draw(int camera_y) const override;
};
