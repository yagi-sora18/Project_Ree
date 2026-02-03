#include "Coin.h"

#include "../../Utillity/ResourceManager.h"
#include <DxLib.h>

#include <cmath>

void Coin::Update(float)
{
	// 毎フレーム同期（pivot/point/box）
	UpdateCollision();
}

void Coin::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
    //取得済みなら描画しない
    if (!active) return;          // もし active フラグがあるなら
    if (collected) return;        // 取得フラグ（名前はあなたのコードに合わせて）

    // ==== 画像のロード（最初に呼ばれたときだけ） ====
    static bool s_loaded = false;
    if (!s_loaded) {
        // 画像の実際のパスはあなたのフォルダ構成に合わせて変更してください
        std::vector<std::string> paths =
        {
            "Resource/Image/Coin_0.png",
            "Resource/Image/Coin_1.png",
            "Resource/Image/Coin_2.png",
            "Resource/Image/Coin_3.png",
        };

        ResourceManager::GetInstance()->LoadAnimImages("coin_spin", paths);
        s_loaded = true;
    }

    //描画に使うハンドル列を取得
    const auto& frames = ResourceManager::GetInstance()->GetAnimImages("coin_spin");
    if (frames.empty())
    {
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

    // ==== 座標計算（少し大きめに描画） ====
    const float SCALE = 1.5f;   //コインの拡大率

    float cx = pos.x + width * 0.5f;
    float cy = pos.y + height * 0.5f;

    float drawW = width * SCALE;
    float drawH = height * SCALE;

    int x0 = (int)(cx - drawW * 0.5f - camera_x + off_x);
    int x1 = (int)(cx + drawW * 0.5f - camera_x + off_x);
    int y0 = (int)(cy - drawH * 0.5f - camera_y + off_y);
    int y1 = (int)(cy + drawH * 0.5f - camera_y + off_y);

    DrawExtendGraph(x0, y0, x1, y1, handle, TRUE);

}