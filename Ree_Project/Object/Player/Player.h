#pragma once
#include "../../Utillity/Vector2D.h"
#include "../../Utillity/Collision.h"

#include "../Object.h"
#include <vector>

class Player : public Object {
public:
    Vector2D vel;
    bool isJumping;
    bool isCharging;
    float chargePower;
    int width;
    int height;
    Collision collision;

    // デフォルトコンストラクタ（宣言）
    Player();

    // CSV等から渡される( x, y, w, h )で生成されるコンストラクタ
    Player(float x, float y, int w, int h);

    // メンバ関数
    void Update(float delta_time) override;
    void ApplyPhysics(const std::vector<Object*>& platforms);
    void UpdateCollision();
    void Draw(int camera_y) const override;
};
