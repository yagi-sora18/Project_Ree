#include "Goal.h"
#include "../../Utillity/ResourceManager.h"
#include <DxLib.h>
#include <cmath>

void Goal::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
    //// ほんのり脈動（アルファと外周）で“光ってる”感じ
    //const int t = GetNowCount() % 1000; // 0..999ms
    //const float s = 0.5f * (1.0f + std::sin(t * 2.0f * 3.1415926f / 1000.0f)); // 0..1
    //const int alpha = 150 + (int)(80 * s);

    //const int x0 = (int)(pos.x - camera_x + off_x);
    //const int y0 = (int)(pos.y - camera_y + off_y);
    //const int x1 = (int)(pos.x + width - camera_x + off_x);
    //const int y1 = (int)(pos.y + height - camera_y + off_y);

    //// 外側のグロー
    //SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
    //DrawBox(x0 - 4, y0 - 4, x1 + 4, y1 + 4, GetColor(255, 255, 100), TRUE);
    //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //// 本体（明るい黄色）
    //DrawBox(x0, y0, x1, y1, GetColor(255, 235, 0), TRUE);

    //// 枠
    //DrawBox(x0, y0, x1, y1, GetColor(255, 255, 180), FALSE);

     // ==== 画像の読み込み（最初の1回だけ）====
    static bool loadedOnce = false;
    if (!loadedOnce) {
        std::vector<std::string> paths = {
            "Resource/Image/Door/Door_01.jpg",
            "Resource/Image/Door/Door_02.jpg",
            "Resource/Image/Door/Door_03.jpg",
            "Resource/Image/Door/Door_04.jpg",
            "Resource/Image/Door/Door_05.jpg",
            "Resource/Image/Door/Door_06.jpg",
            "Resource/Image/Door/Door_07.jpg",
        };
        ResourceManager::GetInstance()->LoadAnimImages("goal_door", paths);
        loadedOnce = true;
    }

    const auto& frames = ResourceManager::GetInstance()->GetAnimImages("goal_door");
    if (frames.empty()) {
        // 読み込み失敗したときは、見えなくならないように四角で代用
        int x0 = (int)(pos.x - camera_x + off_x);
        int y0 = (int)(pos.y - camera_y + off_y);
        int x1 = (int)(pos.x + width - camera_x + off_x);
        int y1 = (int)(pos.y + height - camera_y + off_y);
        DrawBox(x0, y0, x1, y1, GetColor(255, 235, 0), TRUE);
        DrawBox(x0, y0, x1, y1, GetColor(255, 255, 180), FALSE);
        return;
    }

    // ==== アニメ（0.12秒ごとに次の画像）====
    int nowMs = GetNowCount();
    int frameIndex = (nowMs / 120) % (int)frames.size();
    int handle = frames[frameIndex];

    // ==== 描画座標（Goalの四角に合わせて拡大縮小）====
    int x0 = (int)(pos.x - camera_x + off_x);
    int y0 = (int)(pos.y - camera_y + off_y);
    int x1 = (int)(pos.x + width - camera_x + off_x);
    int y1 = (int)(pos.y + height - camera_y + off_y);

    // ちょっと光らせる（なくてもOK）
    SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
    DrawBox(x0 - 6, y0 - 6, x1 + 6, y1 + 6, GetColor(255, 255, 140), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawExtendGraph(x0, y0, x1, y1, handle, TRUE);

}
