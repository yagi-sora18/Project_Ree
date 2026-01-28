// Title.cpp
#include <DxLib.h>
#include "Title.h"
#include "../Utillity/InputControl.h"  // 入力取得用（InGameと同じクラス）:contentReference[oaicite:3]{index=3}
#include "../Utillity/SoundManager.h"

Title::Title() {}

Title::~Title()
{
    if (titleGraph != -1) {
        DeleteGraph(titleGraph);
        titleGraph = -1;
    }
}

void Title::Initialize()
{
    next_scene = eSceneType::eTitle;

    // すでに読み込んでいたら一度破棄
    if (titleGraph != -1) {
        DeleteGraph(titleGraph);
        titleGraph = -1;
    }

    // タイトル画像の読み込み（パスは自分の画像に合わせて変更）
    titleGraph = LoadGraph("Resource/Image/Title3.png");

    // BGMの読む込み
    SoundManager::GetInstance()->PlayBgm("Resource/Sound/BGM_Title.wav");

}

void Title::Update(float dt)
{
    // 入力更新（これを忘れるとどのキーを押しても反応しません）
    auto in = InputControl::GetInstance();
    in->Update();

    // どれかキーが押されたらゲーム開始
    if (in->GetKeyDown(KEY_INPUT_SPACE) ||
        in->GetKeyDown(KEY_INPUT_RETURN) ||   // Enter
        in->GetKeyDown(KEY_INPUT_Z))          // Zキーなど、好みで
    {
        SoundManager::GetInstance()->PlaySe("Resource/Sound/SE_TitleDecide.wav");

        next_scene = eSceneType::eInGame;
    }
}

void Title::Draw()
{
    int sw, sh, cc;
    GetScreenState(&sw, &sh, &cc);   // 画面サイズ取得

    // 背景画像
    if (titleGraph != -1) {
        // 画面全体に伸縮して表示
        DrawExtendGraph(0, 0, sw, sh, titleGraph, TRUE);
    }
    else {
        // 画像読み込み失敗時の代わりの表示
        DrawBox(0, 0, sw, sh, GetColor(0, 0, 80), TRUE);
        DrawString(50, 50, "Title image not found.", GetColor(255, 255, 255));
    }

    //// 画面下あたりに「PRESS START」的な文字を表示
    //const char* msg = "Press SPACE / ENTER to Start";
    //int w = GetDrawStringWidth(msg, (int)strlen(msg));
    //DrawString((sw - w) / 2, sh - 80, msg, GetColor(255, 255, 255));
}
