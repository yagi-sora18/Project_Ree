#pragma once
#include "../Object.h"

class Goal : public Object
{
    public:
        Goal(float x, float y, float w, float h) : Object(x, y, w, h)
        {
            collision.object_type = eGoal;
        }
        void Update(float) override {}
        void Draw(int camera_x, int camera_y, int off_x, int off_y) override;
};