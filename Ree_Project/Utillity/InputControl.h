#pragma once
#include "Enum.h"
#include "Vector2D.h"
#include "DxLib.h"
#include "SingleTone.h"
#include <math.h>

#define KEYCODE_MAX 256
#define DEADZONE 10000.0f

// �L�[�{�[�h�Ή��L�[�R�[�h�iDxLib�j
#define KEY_LEFT   KEY_INPUT_A
#define KEY_RIGHT  KEY_INPUT_D
#define KEY_JUMP   KEY_INPUT_SPACE

class InputControl : public Singleton<InputControl>
{
    friend class Singleton<InputControl>;  // Singleton����̃C���X�^���X��������

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

    // ���͍X�V�i���t���[���Ăяo���j
    void Update();

    // �L�[�{�[�h����
    bool GetKey(int key_code) const;
    bool GetKeyDown(int key_code) const;
    bool GetKeyUp(int key_code) const;

    // �Q�[���p�b�h���́i���ݖ��g�p�j
    eInputState GetPadButtonState(int button) const;
    bool GetButtonDown(int dxlib_pad_const) const;
    Vector2D GetJoyStickLeft() const;
    Vector2D GetJoyStickRight() const;

private:
    bool CheckKeyRange(int key_code) const;
};
