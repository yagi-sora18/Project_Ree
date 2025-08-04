#pragma once
#pragma once
#include "../../Utillity/Vector2D.h"
#include "DxLib.h"

class Coin {
public:
    Vector2D pos;
    bool collected;

    Coin(float x, float y);
    void Draw(int camera_y) const;
};

