#include "Result.h"
#include "../Utillity/InputControl.h"
#include "DxLib.h"

Result::Result() : next_scene(eSceneType::eResult) {}

void Result::Initialize() {}

eSceneType Result::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

    if (input->GetKeyDown(KEY_INPUT_RETURN)) {
        next_scene = eSceneType::eTitle;
    }

    return next_scene;
}

void Result::Draw()
{
    DrawString(220, 200, "Game Clear! Press Enter to return to Title", GetColor(255, 255, 0));
}

void Result::Finalize() {}

eSceneType Result::GetNowSceneType() const
{
    return eSceneType::eResult;
}
