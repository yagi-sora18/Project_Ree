// Unified InputControl.h
#pragma once
#include "Enum.h"
#include "Vector2D.h"
#include "DxLib.h"
#include <math.h>

#define KEYCODE_MAX 256
#define DEADZONE 10000.0f

#define PAD_INPUT_LB         0x0100  // LBボタン（左バンパー）
#define PAD_INPUT_RB         0x0200  // RBボタン（右バンパー）
#define PAD_INPUT_LTRIGGER   0x0400  // LTトリガー
#define PAD_INPUT_RTRIGGER   0x0800  // RTトリガー

class InputControl
{
private:
    static InputControl* instance;

    // キーボード入力
    char now_key[KEYCODE_MAX];
    char old_key[KEYCODE_MAX];

    // パッド入力
    static int pad_now;
    static int pad_old;
    XINPUT_STATE now_pad;

private:
    InputControl() = default;
    InputControl(const InputControl&) = delete;
    InputControl& operator=(const InputControl&) = delete;

public:
    ~InputControl() = default;

    static InputControl* GetInstance();
    static void DeleteInstance();

    void Update();

    // キーボード
    bool GetKey(int key_code) const;
    bool GetKeyDown(int key_code) const;
    bool GetKeyUp(int key_code) const;

    // パッドボタン
    eInputState GetPadButtonState(int button) const;
    bool GetButtonDown(int dxlib_pad_const) const;

    // スティック
    Vector2D GetJoyStickLeft() const;
    Vector2D GetJoyStickRight() const;

private:
    bool CheckKeyRange(int key_code) const;
};
