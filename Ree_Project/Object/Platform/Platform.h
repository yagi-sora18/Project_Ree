#pragma once
#include "../../Utillity/Vector2D.h"
#include "../../Utillity/Collision.h"
#include "DxLib.h"

class Platform
{
public:
    Vector2D pos;
    int width;
    int height;
    Collision collision;

    Platform(float x, float y, int w, int h);
    void UpdateCollision();
    void Draw(int camera_y) const;
};
