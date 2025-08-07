#pragma once
#include "../Utillity/Vector2D.h"

class Object {
public:
    Vector2D pos;
    bool is_active = true;

    Object() = default;
    virtual ~Object() {}

    virtual void Update(float delta_time) {}
    virtual void Draw(int camera_y) const {}
    virtual void OnCollision(Object* other) {}
    virtual bool IsActive() const { return is_active; }
};
