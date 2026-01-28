#include "Result.h"
#include <DxLib.h>
#include "../Utillity/InputControl.h"
#include "../Utillity/SoundManager.h"

void Result::Initialize()
{
	next = eSceneType::eResult;
	SoundManager::GetInstance()->PlayBgm("Resource/Sound/BGM_Result.wav");
}

ResultMode Result::last_mode = ResultMode::GameOver;

Result::Result() {}

Result::~Result()
{
    if (clear_image != -1) { DeleteGraph(clear_image); clear_image = -1; }
    if (over_image != -1) { DeleteGraph(over_image);  over_image = -1; }
}

void Result::SetMode(ResultMode mode)
{
    last_mode = mode;
}

void Result::Initialize()
{
    next_scene = eSceneType::eResult;

    // すでに読み込んでいたら一度消す
    if (clear_image != -1) { DeleteGraph(clear_image); clear_image = -1; }
    if (over_image != -1) { DeleteGraph(over_image);  over_image = -1; }

    // 画像読み込み（プロジェクト内に置いた場所）
    clear_image = LoadGraph("Resource/Image/GameClear.png");
    over_image = LoadGraph("Resource/Image/GameOver.png");
}

void Result::Update(float)
{
    auto* input = InputControl::GetInstance();
    input->Update();

    // ENTER / SPACE：タイトルへ
    if (input->GetKeyDown(KEY_INPUT_RETURN) || input->GetKeyDown(KEY_INPUT_SPACE))
    {
        next_scene = eSceneType::eTitle;
        return;
    }

    // R：もう一回（InGameへ）
    if (input->GetKeyDown(KEY_INPUT_R))
    {
        next_scene = eSceneType::eInGame;
        return;
    }
}

void Result::Draw()
{
    int screen_w, screen_h, color_bit;
    GetScreenState(&screen_w, &screen_h, &color_bit);

    int image = -1;

    if (last_mode == ResultMode::GameClear) image = clear_image;
    else                                   image = over_image;

    if (image != -1)
    {
        // 画面いっぱいに表示
        DrawExtendGraph(0, 0, screen_w, screen_h, image, TRUE);
    }
    else
    {
        // 読み込み失敗時
        DrawBox(0, 0, screen_w, screen_h, GetColor(0, 0, 0), TRUE);
        DrawString(40, 40, "Result image not found.", GetColor(255, 255, 255));
    }

    // 操作説明（右下あたり）
    DrawString(30, screen_h - 60, "ENTER : Title   R : Retry", GetColor(255, 255, 255));
}
