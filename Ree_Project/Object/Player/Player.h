#pragma once
#include <vector>          // ★ これが無くて std::vector 未定義になっていました
#include <algorithm>
#include "../Object.h"

// どこかヘッダの上の方に追加
enum class PlayerAnimeState {
    Idle,      // アイドル
    Walk,      // 歩き
    Charge,    // チャージ中
    Jump,      // ジャンプ中（空中）
    Landing    // 着地直後
};


class Player : public Object {
public:
    Player(float x, float y, float w = 50.0f, float h = 50.0f);

    void Update(float dt) override;
    //void Draw(int camera_y) override;
    //void Draw(int camera_x, int camera_y) override;
    void Draw(int camera_x, int camera_y, int off_x, int off_y) override;

    // ★ dt 付きの物理。宣言と定義を一致させる
    void ApplyPhysics(const std::vector<class Object*>& objects, float dt);

    // ゲージの充填率（0.0〜1.0）。充電中のみ値が出て、非充電時は0を返す
    float GetChargeRatio() const;
    bool  IsCharging() const { return charging; }


private:
    Vector2D vel{ 0,0 };
    bool isJumping{ false };

private:
    // アニメ用の状態
    PlayerAnimeState animeState = PlayerAnimeState::Idle;

    // 着地ポーズを少しだけ見せるためのタイマー（任意）
    float landingTimer = 0.0f;

    // チャージジャンプ
    bool  charging{ false };
    float charge_t{ 0.0f };
    static constexpr float CHARGE_MAX = 1.0f;
    static constexpr float JUMP_V0_MIN = 650.0f;
    static constexpr float JUMP_V0_MAX = 1300.0f;

    // 移動/物理
    static constexpr float A_GROUND = 2800.0f;
    static constexpr float A_AIR = 600.0f;
    static constexpr float FRICTION_GROUND = 1800.0f;
    static constexpr float FRICTION_AIR = 300.0f;
    static constexpr float GRAVITY = 3000.0f;
};
