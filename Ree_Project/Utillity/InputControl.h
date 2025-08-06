#pragma once
#include "Enum.h"
#include "Vector2D.h"
#include "DxLib.h"
#include "SingleTone.h"
#include <math.h>

#define KEYCODE_MAX 256
#define DEADZONE 10000.0f

// キーボード対応キーコード（DxLib）
#define KEY_LEFT   KEY_INPUT_A
#define KEY_RIGHT  KEY_INPUT_D
#define KEY_JUMP   KEY_INPUT_SPACE

class InputControl : public Singleton<InputControl>
{
    friend class Singleton<InputControl>;  // Singletonからのインスタンス生成許可

private:
    char now_key[KEYCODE_MAX];
    char old_key[KEYCODE_MAX];

    static int pad_now;
    static int pad_old;
    XINPUT_STATE now_pad;

    InputControl() = default;
    InputControl(const InputControl&) = delete;
    InputControl& operator=(const InputControl&) = delete;

public:
    ~InputControl() = default;

    // 入力更新（毎フレーム呼び出す）
    void Update();

    // キーボード入力
    bool GetKey(int key_code) const;
    bool GetKeyDown(int key_code) const;
    bool GetKeyUp(int key_code) const;

    // ゲームパッド入力（現在未使用）
    eInputState GetPadButtonState(int button) const;
    bool GetButtonDown(int dxlib_pad_const) const;
    Vector2D GetJoyStickLeft() const;
    Vector2D GetJoyStickRight() const;

private:
    bool CheckKeyRange(int key_code) const;
};
