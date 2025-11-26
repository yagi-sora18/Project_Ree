#include "Coin.h"

#include "../../Utillity/ResourceManager.h"
#include <DxLib.h>

#include <cmath>


static constexpr float GAME_OFF_X = 250.0f;


void Coin::Update(float) {
	// 毎フレーム同期（pivot/point/box）
	UpdateCollision();
}


//void Coin::Draw(int camera_y) 

//void Coin::Draw(int camera_x, int camera_y) {
//	if (collected) return;
//	//int x = (int)(pos.x - GAME_OFF_X);
//	int x = (int)(pos.x - camera_x);
//	int y = (int)(pos.y - camera_y);
//	DrawCircle(x + (int)width / 2, y + (int)height / 2, (int)(width / 2), GetColor(255, 215, 0), true);
//}

//void Coin::Draw(int camera_x, int camera_y, int off_x, int off_y)
//{
//	if (collected) return;
//
//	int x = (int)(pos.x - camera_x + off_x);
//	int y = (int)(pos.y - camera_y + off_y);
//
//	DrawCircle(x + (int)width / 2, y + (int)height / 2, (int)(width / 2), GetColor(255, 215, 0), true);
//}

void Coin::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
    //取得済みなら描画しない
    if (!active) return;          // もし active フラグがあるなら
    if (collected) return;        // 取得フラグ（名前はあなたのコードに合わせて）

    // ==== 画像のロード（最初に呼ばれたときだけ） ====
    static bool s_loaded = false;
    if (!s_loaded) {
        // 画像の実際のパスはあなたのフォルダ構成に合わせて変更してください
        // 例: "Resource/Image/Coin_0.png" など
        std::vector<std::string> paths = {
            "Resource/Image/Coin_0.png",
            "Resource/Image/Coin_1.png",
            "Resource/Image/Coin_2.png",
            "Resource/Image/Coin_3.png",
        };

        ResourceManager::GetInstance()->LoadAnimImages("coin_spin", paths);
        s_loaded = true;
    }

    // ==== 描画に使うハンドル列を取得 ====
    const auto& frames = ResourceManager::GetInstance()->GetAnimImages("coin_spin");
    if (frames.empty()) {
        // 読み込み失敗時は、今まで通り円で描画しておく（保険）
        int cx = (int)(pos.x - camera_x + off_x + width * 0.5f);
        int cy = (int)(pos.y - camera_y + off_y + height * 0.5f);
        int r = (int)(width * 0.5f);
        DrawCircle(cx, cy, r, GetColor(255, 255, 0), TRUE);
        return;
    }

    // ==== アニメーションフレームを決める ====
    // 120ms ごとに次のコマへ（約 8fps）
    int t = GetNowCount();
    int frame = (t / 120) % (int)frames.size();
    int handle = frames[frame];

    // ==== 座標計算（オブジェクトの矩形に合わせて伸縮描画） ====
    int x0 = (int)(pos.x - camera_x + off_x);
    int y0 = (int)(pos.y - camera_y + off_y);
    int x1 = (int)(pos.x + width - camera_x + off_x);
    int y1 = (int)(pos.y + height - camera_y + off_y);

    // 枠にピッタリはめて描画
    DrawExtendGraph(x0, y0, x1, y1, handle, TRUE);
}