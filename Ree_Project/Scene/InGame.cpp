#include "InGame.h"
#include "../Object/Player/Player.h"
#include "../Object/Platform/Platform.h"
#include "../Object/Item/Coin.h"
#include "../Object/Wall/Wall.h"
#include "../Map/MapLoader.h"
#include "../Utillity/InputControl.h"
#include <algorithm>
#include <DxLib.h>

// マクロ衝突やC++標準に依存しない自前関数
template<typename T>
static inline T Clamp(T v, T lo, T hi) { return (v < lo) ? lo : (v > hi) ? hi : v; }
template<typename T>
static inline T Max(T a, T b) { return (a < b) ? b : a; }
template<typename T>
static inline T Min(T a, T b) { return (a < b) ? a : b; }


InGame::InGame() {}


void InGame::Initialize() {
	player = nullptr;
	object_manager.ClearAll();


	std::vector<Player> tP;
	std::vector<Platform> tPf;
	std::vector<Coin> tC;
	std::vector<Wall> tW;


	//LoadMapFromCSV("Resource/Map/map01.csv", tP, tPf, tC, tW);

	LoadMapFromCSV("Resource/Map/map01.csv", tP, tPf, tC, tW, 50, &map_w_px, &map_h_px);


	for (const auto& P : tPf) object_manager.Add(new Platform(P.pos.x, P.pos.y, P.width, P.height));
	for (const auto& C : tC) object_manager.Add(new Coin(C.pos.x, C.pos.y, C.width, C.height));
	for (const auto& W : tW) object_manager.Add(new Wall(W.pos.x, W.pos.y, W.width, W.height));


	if (!tP.empty()) {
		const auto& P = tP.front();
		player = new Player(P.pos.x, P.pos.y, P.width, P.height);
	}
	else {
		player = new Player(300, 300, 50, 50);
	}
	object_manager.Add(player);


	camera_y = 0; now_scene = eSceneType::eInGame; next_scene = eSceneType::eInGame;

	// 画面サイズに合わせて右下端に寄せる
	const int SCREEN_W = 1280;
	const int SCREEN_H = 720;
	camera_x = Max(0, map_w_px - SCREEN_W);
	camera_y = Max(0, map_h_px - SCREEN_H);
	now_scene = eSceneType::eInGame; next_scene = eSceneType::eInGame;
}


void InGame::Update(float dt) {
	InputControl::GetInstance()->Update();
	object_manager.UpdateAll(dt);


	// カメラ（デッドゾーン）
	//const int viewH = 720; // 画面高さに合わせて

	const int SCREEN_W = 1280;
	const int SCREEN_H = 720;

	// 縦カメラ：デッドゾーン
	/*const int DZ_TOP = viewH * 2 / 5;
	const int DZ_BOT = viewH * 3 / 5;*/

	const int DZ_TOP = SCREEN_H * 2 / 5;
	const int DZ_BOT = SCREEN_H * 3 / 5;

	int py = (int)player->pos.y - camera_y;
	if (py < DZ_TOP) camera_y -= (DZ_TOP - py);
	else if (py > DZ_BOT) camera_y += (py - DZ_BOT);

	//if (camera_y < 0) camera_y = 0;
	// 右下端へ寄せたい：横は常に右端に張り付け、両軸をクランプ
	camera_x = Max(0, map_w_px - SCREEN_W);
	camera_y = Clamp(camera_y, 0, Max(0, map_h_px - SCREEN_H));

	if (InputControl::GetInstance()->GetKeyDown(KEY_INPUT_ESCAPE)) {
		next_scene = eSceneType::eResult;
	}
}


void InGame::Draw() {
	//object_manager.DrawAll(camera_y);
	object_manager.DrawAll(camera_x, camera_y);
	DrawFormatString(20, 20, GetColor(255, 255, 255), "Score:%d", object_manager.GetScore());

	// —— ここまででゲーム世界の描画が終わっている想定 ——
	int sw, sh, cc;
	GetScreenState(&sw, &sh, &cc);

	const int margin = 12;
	const int panelW = 240;
	const int panelH = 110;
	const int px = sw - panelW - margin;
	const int py = margin;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(px, py, px + panelW, py + panelH, GetColor(20, 25, 40), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(px, py, px + panelW, py + panelH, GetColor(70, 80, 120), FALSE);

	DrawString(px + 12, py + 10, _T("操作"), GetColor(220, 230, 255));
	DrawString(px + 12, py + 42, _T("[A] 左に移動"), GetColor(200, 210, 230));
	DrawString(px + 12, py + 42 + 22, _T("[D] 右に移動"), GetColor(200, 210, 230));
	DrawString(px + 12, py + 42 + 44, _T("[SPACE] ジャンプ"), GetColor(200, 210, 230));

}