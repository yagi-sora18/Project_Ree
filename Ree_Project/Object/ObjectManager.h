#pragma once
#include <vector>       // ★ std::vector 用
#include <algorithm>    // ★ std::remove_if 用
#include "Object.h"     // ★ Object クラスを参照するため

class ObjectManager {
private:
    std::vector<Object*> objects;
    int score = 0; // スコア変数

public:
    ~ObjectManager();

    void Add(Object* obj);
    void UpdateAll(float delta_time);
    void DrawAll(int camera_y);
    void ClearAll();

    const std::vector<Object*>& GetObjects() const { return objects; }

    // スコア操作
    void AddScore(int value) { score += value; }
    int GetScore() const { return score; }
    void ResetScore() { score = 0; }
};
