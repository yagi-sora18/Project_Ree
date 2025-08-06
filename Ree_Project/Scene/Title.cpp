#include "Title.h"
#include "../Utillity/InputControl.h"
#include "DxLib.h"

Title::Title() : next_scene(eSceneType::eTitle) {}

void Title::Initialize() {}

eSceneType Title::Update(float delta_second)
{
    InputControl* input = InputControl::GetInstance();

    if (input->GetKeyDown(KEY_INPUT_RETURN)) {
        next_scene = eSceneType::eInGame;
    }

    return next_scene;
}

void Title::Draw()
{
    DrawString(280, 200, "Press Enter to Start", GetColor(255, 255, 255));

    if (InputControl::GetInstance()->GetKey(KEY_INPUT_RETURN)) {
        DrawString(100, 100, "ENTER: PRESSED", GetColor(255, 0, 0));
    }
}

void Title::Finalize() {}

eSceneType Title::GetNowSceneType() const
{
    return eSceneType::eTitle;
}
