#include "Goal.h"
#include <DxLib.h>
#include <cmath>

void Goal::Draw(int camera_x, int camera_y, int off_x, int off_y) {
    // ほんのり脈動（アルファと外周）で“光ってる”感じ
    const int t = GetNowCount() % 1000; // 0..999ms
    const float s = 0.5f * (1.0f + std::sin(t * 2.0f * 3.1415926f / 1000.0f)); // 0..1
    const int alpha = 150 + (int)(80 * s);

    const int x0 = (int)(pos.x - camera_x + off_x);
    const int y0 = (int)(pos.y - camera_y + off_y);
    const int x1 = (int)(pos.x + width - camera_x + off_x);
    const int y1 = (int)(pos.y + height - camera_y + off_y);

    // 外側のグロー
    SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
    DrawBox(x0 - 4, y0 - 4, x1 + 4, y1 + 4, GetColor(255, 255, 100), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // 本体（明るい黄色）
    DrawBox(x0, y0, x1, y1, GetColor(255, 235, 0), TRUE);

    // 枠
    DrawBox(x0, y0, x1, y1, GetColor(255, 255, 180), FALSE);
}
