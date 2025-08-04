// Unified InputControl.h
#pragma once
#include "Enum.h"
#include "Vector2D.h"
#include "DxLib.h"
#include <math.h>

#define KEYCODE_MAX 256
#define DEADZONE 10000.0f

#define PAD_INPUT_LB         0x0100  // LB�{�^���i���o���p�[�j
#define PAD_INPUT_RB         0x0200  // RB�{�^���i�E�o���p�[�j
#define PAD_INPUT_LTRIGGER   0x0400  // LT�g���K�[
#define PAD_INPUT_RTRIGGER   0x0800  // RT�g���K�[

class InputControl
{
private:
    static InputControl* instance;

    // �L�[�{�[�h����
    char now_key[KEYCODE_MAX];
    char old_key[KEYCODE_MAX];

    // �p�b�h����
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

    // �L�[�{�[�h
    bool GetKey(int key_code) const;
    bool GetKeyDown(int key_code) const;
    bool GetKeyUp(int key_code) const;

    // �p�b�h�{�^��
    eInputState GetPadButtonState(int button) const;
    bool GetButtonDown(int dxlib_pad_const) const;

    // �X�e�B�b�N
    Vector2D GetJoyStickLeft() const;
    Vector2D GetJoyStickRight() const;

private:
    bool CheckKeyRange(int key_code) const;
};
