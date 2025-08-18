#include "Coin.h"

Coin::Coin(float x, float y) {
    pos = Vector2D(x, y);
    collected = false;

    // �����蔻���������
    collision.pivot = pos + Vector2D(10, 10);
    collision.box_size = Vector2D(20, 20);
    collision.point[0] = pos;
    collision.point[1] = pos + Vector2D(20, 20);
    collision.object_type = eCastle; // ���^�C�v
}

void Coin::Update(float delta_time) {
    // �ʒu�ɍ��킹�ē����蔻����X�V
    collision.pivot = pos + Vector2D(10, 10);
}

void Coin::Draw(int camera_y) const {
    if (!collected) {
        DrawCircle(
            (int)pos.x,
            (int)(pos.y - camera_y),
            10,
            GetColor(255, 255, 0),
            TRUE
        );
    }
}



