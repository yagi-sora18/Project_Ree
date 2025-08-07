#pragma once
#include "../../Utillity/Vector2D.h"
#include "../Object.h"
#include "DxLib.h"

class Coin : public Object {
public:
    bool collected;

    Coin(float x, float y);
    void Update(float delta_time) override {}
    void Draw(int camera_y) const override;
};
