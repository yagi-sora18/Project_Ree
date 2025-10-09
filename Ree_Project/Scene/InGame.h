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


    // InGame.h （private に追加）
    struct MiniMapState {
        int x, y, w, h;           // 左パネル内の表示矩形
        float minx, miny, maxx, maxy; // ワールド境界（自動更新）
    };
    MiniMapState mmini;

    // 追加メソッド宣言
    void MiniMap_SetRect(int x, int y, int w, int h);
    void MiniMap_UpdateBounds();
    void MiniMap_Draw() const;

};
