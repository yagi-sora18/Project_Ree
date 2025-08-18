#include "Coin.h"

Coin::Coin(float x, float y) {
    pos = Vector2D(x, y);
    collected = false;
}

void Coin::Draw(int camera_y) const {
    if (!collected) {
        DrawCircle((int)pos.x, (int)(pos.y - camera_y), 10, GetColor(255, 255, 0), TRUE);
    }
}


