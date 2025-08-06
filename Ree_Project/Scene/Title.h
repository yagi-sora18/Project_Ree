#pragma once
#include "SceneBase.h"

class Title : public SceneBase
{
private:
    eSceneType next_scene;

public:
    Title();
    void Initialize() override;
    eSceneType Update(float delta_second) override;
    void Draw() override;
    void Finalize() override;
    eSceneType GetNowSceneType() const override;
};
