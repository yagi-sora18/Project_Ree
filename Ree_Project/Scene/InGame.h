#pragma once
#include "SceneBase.h"
#include "../Object/ObjectManager.h"
#include <vector>


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

	float time_limit = 0.0f;        // 残り時間（秒）
	int   next_time_bonus_score = 0; // 次に時間ボーナスをもらえるスコア閾値
	float dead_line_y = 0.0f;  // ここより下に落ちたらゲームオーバー

	int background_image = -1;

	const std::vector<int>* charge_gauge_images{ nullptr };

	eSceneType now_scene{ eSceneType::eInGame };
	eSceneType next_scene{ eSceneType::eInGame };
};