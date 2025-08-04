#pragma once
#include "../../Utillity/Vector2D.h"
#include "../../Utillity/Collision.h"
#include <vector>

class Platform;

class Player {
public:
    Vector2D pos;
    Vector2D vel;
    bool isJumping;
    bool isCharging;
    float chargePower;
    Collision collision;

    Player();
    void Update();
    void ApplyPhysics(const std::vector<Platform>& platforms);
    void UpdateCollision();
    void Draw(int camera_y) const;
};
