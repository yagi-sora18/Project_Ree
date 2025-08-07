#pragma once
#include <vector>
#include "Object.h"

class ObjectManager {
private:
    std::vector<Object*> objects;

public:
    ~ObjectManager();

    void Add(Object* obj);
    void UpdateAll(float delta_time);
    void DrawAll(int camera_y);
    void ClearAll();

    const std::vector<Object*>& GetObjects() const { return objects; }
};
