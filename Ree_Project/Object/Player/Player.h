#pragma once
#include "../../Utillity/Vector2D.h"

class Player {
public:
    Vector2D pos;
    Vector2D vel;
    bool isJumping;
    bool isCharging;
    float chargePower;

    Player();
    void Update();
    void Draw() const;
};


