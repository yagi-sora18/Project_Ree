#include "InGame.h"
#include "../Object/Player/Player.h"
#include "../Object/Platform/Platform.h"
#include "../Object/Item/Coin.h"
#include "../Object/Wall/Wall.h"
#include "../Object/Goal/Goal.h"
#include "Result.h"
#include "../Map/MapLoader.h"
#include "../Utillity/InputControl.h"
#include "../Utillity/ResourceManager.h"
#include "../Utillity/SoundManager.h"
#include <algorithm>
#include <DxLib.h>

// マクロ衝突やC++標準に依存しない自前関数
template<typename T>
static inline T Clamp(T v, T lo, T hi) { return (v < lo) ? lo : (v > hi) ? hi : v; }
template<typename T>
static inline T Max(T a, T b) { return (a < b) ? b : a; }
template<typename T>
static inline T Min(T a, T b) { return (a < b) ? a : b; }


// 色補間ユーティリティ（0..1）
static inline int LerpI(int a, int b, float t) 
{
	if (t < 0.0f) t = 0.0f; else if (t > 1.0f) t = 1.0f;

	return a + (int)((b - a) * t);

}

// 0→赤(255,0,0), 0.5→黄(255,255,0), 1→緑(0,255,0)
static inline int GaugeColorFromRatio(float r) 
{
	if (r < 0.0f) r = 0.0f; else if (r > 1.0f) r = 1.0f;

	int R, G;

	if (r <= 0.5f) 
	{
		float t = r / 0.5f;          // 0→赤, 0.5→黄

		R = 255;

		G = LerpI(0, 255, t);

	}
	else 
	{
		float t = (r - 0.5f) / 0.5f; // 0.5→黄, 1→緑

		R = LerpI(255, 0, t);

		G = 255;

	}

	return GetColor(R, G, 0);

}


InGame::InGame() {}


void InGame::Initialize() {
	player = nullptr;
	object_manager.ClearAll();


	std::vector<Player> tP;
	std::vector<Platform> tPf;
	std::vector<Coin> tC;
	std::vector<Wall> tW;
	std::vector<Goal> tG;


	//LoadMapFromCSV("Resource/Map/map01.csv", tP, tPf, tC, tW);

	LoadMapFromCSV("Resource/Map/map01.csv", tP, tPf, tC, tW, tG, 50, &map_w_px, &map_h_px);


	for (const auto& P : tPf) object_manager.Add(new Platform(P.pos.x, P.pos.y, P.width, P.height));
	for (const auto& C : tC) object_manager.Add(new Coin(C.pos.x, C.pos.y, C.width, C.height));
	for (const auto& W : tW) object_manager.Add(new Wall(W.pos.x, W.pos.y, W.width, W.height));
	for (const auto& G : tG)  object_manager.Add(new Goal(G.pos.x, G.pos.y, G.width, G.height)); // ★ ゴール生成

	auto* rm = ResourceManager::GetInstance();
	std::vector<std::string> gauge_paths = {
		"Resource/Image/gage/Gage1.PNG",
		"Resource/Image/gage/Gage2.PNG",
		"Resource/Image/gage/Gage3.PNG",
		"Resource/Image/gage/Gage4.PNG",
		"Resource/Image/gage/Gage5.PNG",
		"Resource/Image/gage/Gage6.PNG",
		"Resource/Image/gage/Gage7.PNG",
		"Resource/Image/gage/Gage8.PNG",
	};
	rm->LoadAnimImages("charge_gage", gauge_paths);
	charge_gauge_images = &rm->GetAnimImages("charge_gage");

	SoundManager::GetInstance()->PlayBgm("Resource/Sound/BGM_InGame.wav");


	if (!tP.empty()) 
	{
		const auto& P = tP.front();
		player = new Player(P.pos.x, P.pos.y, P.width, P.height);
	}
	else 
	{
		player = new Player(300, 300, 50, 50);
	}
	object_manager.Add(player);


	camera_y = 0; now_scene = eSceneType::eInGame; next_scene = eSceneType::eInGame;

	// ★ 制限時間の初期値（1分 = 60秒）
	time_limit = 180.0f;

	// ★ 何点ごとに時間ボーナスを与えるか
	//   ここでは「コイン1個 10点」として「50点ごとに+10秒」のイメージ
	const int SCORE_PER_BONUS = 50;
	next_time_bonus_score = SCORE_PER_BONUS;

	// 画面サイズに合わせて右下端に寄せる

	/*const int SCREEN_W = 1280;
	const int SCREEN_H = 720;
	camera_x = Max(0, map_w_px - SCREEN_W);
	camera_y = Max(0, map_h_px - SCREEN_H);*/
	const int SCREEN_W = 1330;
	const int SCREEN_H = 720;

	  // 横：マップが狭ければ camera_x=0 にして、右寄せオフセットを足す → 左側が空白になる
	if (map_w_px >= SCREEN_W)
	{
		camera_x = Max(0, map_w_px - SCREEN_W); 
		screen_off_x = 0;
	}
	else
	{
		camera_x = 0;
		screen_off_x = SCREEN_W - map_w_px;
	}
	// 縦：右下基準を維持（マップが低ければ下に寄せる＝上が空白）
	if (map_h_px >= SCREEN_H)
	{
		camera_y = Max(0, map_h_px - SCREEN_H);
		screen_off_y = 0;
	}
	 else
	{ 
		camera_y = 0;
		screen_off_y = SCREEN_H - map_h_px;
	}

	bg_image = LoadGraph("Resource/Image/Background.png");

	// 読み込み失敗チェック（-1 なら失敗）
	if (bg_image == -1) {
		printfDx("背景画像の読み込みに失敗: Resource/Image/InGameBG.png\n");
	}


	// 「開始時点の画面下端（世界座標）」をデッドラインにする（固定）
	dead_line_y = (float)camera_y + (SCREEN_H - (float)screen_off_y) + 200.0f;


	now_scene = eSceneType::eInGame;

	SoundManager::GetInstance()->PlaySe("Resource/Sound/SE_Goal.wav");

	next_scene = eSceneType::eInGame;
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
	//右端固定＆クランプ
	/*camera_x = Max(0, map_w_px - SCREEN_W);
	camera_y = Clamp(camera_y, 0, Max(0, map_h_px - SCREEN_H));*/

	// 横：マップが画面より広いなら右端固定／狭いなら常に camera_x=0（左側空白を維持）

	if (map_w_px >= SCREEN_W) camera_x = Max(0, map_w_px - SCREEN_W);
	else camera_x = 0;

	// 縦：クランプ（マップが低ければ camera_y=0 のまま、下寄せは screen_off_y で表現）

	camera_y = Clamp(camera_y, 0, Max(0, map_h_px - SCREEN_H));

	// === 制限時間のカウントダウン ===
	if (time_limit > 0.0f) {
		time_limit -= dt;
		if (time_limit <= 0.0f) {
			time_limit = 0.0f;

			// ★ 時間切れになったらリザルトへ
			next_scene = eSceneType::eResult;
		}
	}

	// === コイン一定量で時間ボーナス ===
	{
		const int SCORE_PER_BONUS = 50;   // 何点ごとに…
		const float TIME_BONUS = 10.0f;   // 何秒増やすか

		int currentScore = object_manager.GetScore();

		// 一度にたくさんスコアを稼いだ場合に備えて while にしておく
		while (currentScore >= next_time_bonus_score) {
			time_limit += TIME_BONUS;
			next_time_bonus_score += SCORE_PER_BONUS;
		}
	}

	// ★ ゴール到達チェック（Player と Goal のAABB）
	{
		for (auto* obj : object_manager.GetObjects()) 
		{
			if (!obj || !obj->IsActive()) continue;
			if (obj->collision.object_type != eGoal) continue;
			if (IsCheckCollision(player->collision, obj->collision)) 
			{
				Result::SetMode(ResultMode::GameClear);
				next_scene = eSceneType::eResult;
				break;

			}
			
		}
	}

	if (player && player->pos.y > dead_line_y)
	{
		Result::SetMode(ResultMode::GameOver);
		next_scene = eSceneType::eResult;
		return;
	}


	if (InputControl::GetInstance()->GetKeyDown(KEY_INPUT_ESCAPE)) {
		next_scene = eSceneType::eResult;
	}
}


void InGame::Draw()
{
	// 背景（最初に描く）
	if (bg_image != -1) {
		DrawExtendGraph(0, 0, 1280, 720, bg_image, TRUE);
	}

	//// ===== 溜めゲージ（頭上UI） =====
	//const float r = player->GetChargeRatio();   // 0..1（充電中のみ>0）

	//// 表示位置（プレイヤー頭上）
	//const int gaugeW = 72;
	//const int gaugeH = 10;
	//const int marginUp = 12; // 頭から少し上
	//const int gx = (int)(player->pos.x - camera_x + screen_off_x + player->width * 0.5f - gaugeW * 0.5f);
	//const int gy = (int)(player->pos.y - camera_y + screen_off_y - marginUp - gaugeH);

	//// 画面外ならスキップ（軽いカリング）
	//const int SCREEN_W = 1280, SCREEN_H = 720;

	//if (!(gx > SCREEN_W || gy > SCREEN_H || gx + gaugeW < 0 || gy + gaugeH < 0))
	//{
	//	// 背景（半透明）＋枠
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	//	DrawBox(gx, gy, gx + gaugeW, gy + gaugeH, GetColor(20, 25, 40), TRUE);
	//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	DrawBox(gx, gy, gx + gaugeW, gy + gaugeH, GetColor(220, 220, 240), FALSE);

	//	// 充填部分
	//	const int fillW = (int)(gaugeW * r);

	//	if (fillW > 0)
	//	{
	//		const int col = GaugeColorFromRatio(r); // 赤→黄→緑

	//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);

	//		DrawBox(gx + 1, gy + 1, gx + 1 + fillW - 2, gy + gaugeH - 1, col, TRUE);

	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//	}
	//}

	//object_manager.DrawAll(camera_y);
	//object_manager.DrawAll(camera_x, camera_y);
	object_manager.DrawAll(camera_x, camera_y, screen_off_x, screen_off_y);

	// ===== 溜めゲージ（頭上UI） =====
	if (player && player->IsCharging() && charge_gauge_images && !charge_gauge_images->empty())
	{
		const float r = player->GetChargeRatio();   // 0..1

		// 表示サイズ（大きすぎる場合はここを調整）
		const int gaugeW = 110;
		const int gaugeH = 60;
		const int marginUp = 10;

		//int gx = static_cast<int>(player->GetPosX()) - gaugeW / 2;
		//int gy = static_cast<int>(player->GetPosY()) - marginUp - gaugeH;

		const int gx = (int)(player->pos.x - camera_x + screen_off_x + player->width * 0.5f - gaugeW * 0.5f);
		const int gy = (int)(player->pos.y - camera_y + screen_off_y - marginUp - gaugeH);

		const int frameCount = static_cast<int>(charge_gauge_images->size());
		int frameIndex = static_cast<int>(r * frameCount);
		if (frameIndex < 0) frameIndex = 0;
		if (frameIndex >= frameCount) frameIndex = frameCount - 1;

		const int handle = (*charge_gauge_images)[frameIndex];
		DrawExtendGraph(gx, gy, gx + gaugeW, gy + gaugeH, handle, TRUE);
	}


	// スコア表示
	DrawFormatString(20, 20, GetColor(255, 255, 255), "Score:%d", object_manager.GetScore());

	int white = GetColor(255, 255, 255);

	// === 制限時間表示（スコアの下） ===
	{
		// 負になることがないように
		int t = (int)time_limit;
		if (t < 0) t = 0;

		int minutes = t / 60;
		int seconds = t % 60;

		// 残り30秒以下で色を変えるなどしても良い（ここでは例として赤っぽく）
		int timeColor = (t <= 20) ? GetColor(255, 80, 80) : white;

		DrawFormatString(20, 40, timeColor, "Time: %02d:%02d", minutes, seconds);
	}

	// ここまでは同じ
	int sw, sh, cc;
	GetScreenState(&sw, &sh, &cc);

	const int margin = 12;
	const int panelW = 240;   // 元の幅
	const int panelH = 110;

	// 配置とサイズの微調整
	const int offsetY = 60;    // 少しだけ下に
	const int trimRight = 40;   // 右側を短く（px からの幅を縮める）

	// 左上基準
	const int px = margin;
	const int py = margin + offsetY;

	// 実際に使うボックスの右端（短くする）
	const int boxLeft = px;
	const int boxTop = py;
	const int boxRight = px + panelW - trimRight;
	const int boxBottom = py + panelH;

	// ブレンド＆パネル描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(boxLeft, boxTop, boxRight, boxBottom, GetColor(20, 25, 40), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(boxLeft, boxTop, boxRight, boxBottom, GetColor(70, 80, 120), FALSE);

	// テキストは左上からの相対でそのまま
	DrawString(boxLeft + 12, boxTop + 10, _T("操作"), GetColor(220, 230, 255));
	DrawString(boxLeft + 12, boxTop + 42, _T("[A] 左に移動"), GetColor(200, 210, 230));
	DrawString(boxLeft + 12, boxTop + 64, _T("[D] 右に移動"), GetColor(200, 210, 230));
	DrawString(boxLeft + 12, boxTop + 86, _T("[SPACE] ジャンプ"), GetColor(200, 210, 230));


}
