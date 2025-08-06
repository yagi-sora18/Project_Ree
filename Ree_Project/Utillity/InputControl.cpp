#include "InputControl.h"
#include <string.h>

int InputControl::pad_now = 0;
int InputControl::pad_old = 0;

void InputControl::Update()
{
    memcpy(old_key, now_key, sizeof(now_key));
    GetHitKeyStateAll(now_key);  // DxLibの全キー状態を取得

    pad_old = pad_now;
    pad_now = GetJoypadInputState(DX_INPUT_PAD1);
    GetJoypadXInputState(DX_INPUT_PAD1, &now_pad); // スティック
}

// === キーボード ===

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

// === パッド ===（使わないが残しておく）

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

Vector2D InputControl::GetJoyStickRight() const
{
    float x = static_cast<float>(now_pad.ThumbRX);
    float y = static_cast<float>(now_pad.ThumbRY);

    // デッドゾーン処理
    if (fabsf(x) < DEADZONE) x = 0;
    if (fabsf(y) < DEADZONE) y = 0;

    return Vector2D(x / 32768.0f, y / 32768.0f);
}

bool InputControl::CheckKeyRange(int key_code) const
{
    return 0 <= key_code && key_code < KEYCODE_MAX;
}
