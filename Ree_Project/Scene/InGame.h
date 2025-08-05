#pragma once
#include "SceneBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Platform/Platform.h"
#include "../Object/Item/Coin.h"

class InGame : public SceneBase
{
public:
    InGame();
    ~InGame();

    void Update() override;
    void Draw() override;

private:
    Player player;
    std::vector<Platform> platforms;
    std::vector<Coin> coins;
    int camera_y;
};
