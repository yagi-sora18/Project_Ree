#include "Platform.h"

Platform::Platform(float x, float y, int w, int h)
    : pos(x, y), width(w), height(h)
{
    UpdateCollision();
}

void Platform::UpdateCollision()
{
    collision.pivot = pos + Vector2D(width / 2.0f, height / 2.0f);
    collision.box_size = Vector2D(width, height);
    collision.point[0] = pos;
    collision.point[1] = pos + Vector2D(width, height);
    collision.object_type = eCastle;
}

void Platform::Draw(int camera_y) const
{
    DrawBox((int)pos.x, (int)(pos.y - camera_y),
        (int)(pos.x + width), (int)(pos.y + height - camera_y),
        GetColor(100, 100, 255), TRUE);
}
