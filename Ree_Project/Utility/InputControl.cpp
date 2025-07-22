#include "InputControl.h"
#include <string.h>

InputControl* InputControl::instance = nullptr;
int InputControl::pad_now = 0;
int InputControl::pad_old = 0;

InputControl* InputControl::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new InputControl();
    }
    return instance;
}

void InputControl::DeleteInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

void InputControl::Update()
{
    memcpy(old_key, now_key, sizeof(now_key));
    GetHitKeyStateAll(now_key);

    pad_old = pad_now;
    pad_now = GetJoypadInputState(DX_INPUT_PAD1);
    GetJoypadXInputState(DX_INPUT_PAD1, &now_pad); // スティック用
}

bool InputControl::GetKey(int key_code) const
{
    return CheckKeyRange(key_code) && now_key[key_code] != 0;
}

bool InputControl::GetKeyDown(int key_code) const
{
    return CheckKeyRange(key_code) && now_key[key_code] != 0 && old_key[key_code] == 0;
}

bool InputControl::GetKeyUp(int key_code) const
{
    return CheckKeyRange(key_code) && now_key[key_code] == 0 && old_key[key_code] != 0;
}

eInputState InputControl::GetPadButtonState(int button) const
{
    bool now = (pad_now & button) != 0;
    bool old = (pad_old & button) != 0;

    if (now && !old) return eInputState::ePress;
    if (now && old)  return eInputState::eHeld;
    if (!now && old) return eInputState::eRelease;
    return eInputState::eNone;
}

bool InputControl::GetButtonDown(int dxlib_pad_const) const
{
    return (pad_now & dxlib_pad_const) && !(pad_old & dxlib_pad_const);
}

Vector2D InputControl::GetJoyStickLeft() const
{
    return Vector2D(now_pad.ThumbLX, now_pad.ThumbLY);
}

//Vector2D InputControl::GetJoyStickRight() const
//{
//    return Vector2D(now_pad.ThumbRX, now_pad.ThumbRY);
//}
Vector2D InputControl::GetJoyStickRight() const
{
    float x = static_cast<float>(now_pad.ThumbRX);
    float y = static_cast<float>(now_pad.ThumbRY);

    // デッドゾーン処理（小さい傾きは0扱い）
    if (fabsf(x) < DEADZONE) x = 0;
    if (fabsf(y) < DEADZONE) y = 0;

    // 正規化（-1.0～1.0）
    return Vector2D(x / 32768.0f, y / 32768.0f);
}
bool InputControl::CheckKeyRange(int key_code) const
{
    return 0 <= key_code && key_code < KEYCODE_MAX;
}