#pragma once
#include "SceneBase.h"

// Result画面で表示する種類
enum class ResultMode
{
    GameClear,
    GameOver
};

class Result : public SceneBase {
public:
    Result();
    ~Result();

    // InGameから「どっちの画面を出すか」を渡す
    static void SetMode(ResultMode mode);

    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;
    eSceneType Next() const override { return next_scene; }

private:
    int clear_image = -1;
    int over_image = -1;

    eSceneType next_scene = eSceneType::eResult;

    static ResultMode last_mode; // 直前の結果
};
