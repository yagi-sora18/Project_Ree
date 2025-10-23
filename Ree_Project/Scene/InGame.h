#pragma once
#include "SceneBase.h"
#include "../Object/ObjectManager.h"


class Player;


class InGame : public SceneBase {
public:
	InGame();
	void Initialize() override;
	void Update(float dt) override;
	void Draw() override;
	eSceneType Next() const override { return next_scene; }


private:
	ObjectManager object_manager;
	Player* player{ nullptr };
	//int camera_y{ 0 };//int camera_x{ 0 }, camera_y{ 0 };
	int camera_x{ 0 }, camera_y{ 0 };
	int screen_off_x{ 0 }, screen_off_y{ 0 }; //描画オフセット

	int map_w_px{ 0 }, map_h_px{ 0 };

	eSceneType now_scene{ eSceneType::eInGame };
	eSceneType next_scene{ eSceneType::eInGame };
};