// Title.h
#pragma once
#include "SceneBase.h"

class Title : public SceneBase {
public:
    Title();
    ~Title();

    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;
    eSceneType Next() const override { return next_scene; }

private:
    int titleGraph = -1;              // タイトル画像のハンドル
    eSceneType next_scene = eSceneType::eTitle;
};
