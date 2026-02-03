#include "Goal.h"
#include "../../Utillity/ResourceManager.h"
#include <DxLib.h>
#include <cmath>

void Goal::Draw(int camera_x, int camera_y, int off_x, int off_y)
{
     //画像の読み込み
    static bool loadedOnce = false;
    if (!loadedOnce)
    {
        std::vector<std::string> paths =
        {
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
    if (frames.empty())
    {
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
