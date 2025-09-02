#include "Coin.h"

static const float GAME_OFF_X = 250.0f;


Coin::Coin(float x, float y) {
    pos = Vector2D(x, y);
    collected = false;

    // 当たり判定を初期化
    collision.pivot = pos + Vector2D(10, 10);
    collision.box_size = Vector2D(20, 20);
    collision.point[0] = pos;
    collision.point[1] = pos + Vector2D(20, 20);
    collision.object_type = eCastle; // 仮タイプ
}

void Coin::Update(float delta_time) {
    // 位置に合わせて当たり判定を更新
    collision.pivot = pos + Vector2D(10, 10);
}

void Coin::Draw(int camera_y) const
{
    if (collected) return;
    DrawCircle((int)(pos.x + GAME_OFF_X), (int)(pos.y - camera_y),
        10, GetColor(255, 255, 0), TRUE);
}