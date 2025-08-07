#pragma once
#include "SceneBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Platform/Platform.h"
#include "../Object/Item/Coin.h"
#include "../Object/ObjectManager.h"
#include <vector>

class InGame : public SceneBase
{
public:
    InGame();
    ~InGame();

    void Initialize() override;
    eSceneType Update(float delta_second) override;
    void Draw() override;
    void Finalize() override;
    eSceneType GetNowSceneType() const override;

private:
    Player* player;
    ObjectManager object_manager;
    int camera_y;
    eSceneType now_scene;
    eSceneType next_scene;
};
