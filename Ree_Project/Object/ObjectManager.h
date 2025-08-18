#pragma once
#include <vector>       // �� std::vector �p
#include <algorithm>    // �� std::remove_if �p
#include "Object.h"     // �� Object �N���X���Q�Ƃ��邽��

class ObjectManager {
private:
    std::vector<Object*> objects;
    int score = 0; // �X�R�A�ϐ�

public:
    ~ObjectManager();

    void Add(Object* obj);
    void UpdateAll(float delta_time);
    void DrawAll(int camera_y);
    void ClearAll();

    const std::vector<Object*>& GetObjects() const { return objects; }

    // �X�R�A����
    void AddScore(int value) { score += value; }
    int GetScore() const { return score; }
    void ResetScore() { score = 0; }
};
