#include "InputControl.h"
#include <DxLib.h>
#include <cstring>

void InputControl::Update() {
    std::memcpy(old_key, now_key, sizeof(now_key));
    GetHitKeyStateAll(now_key);  // �� char[256] �Ō^��v
}
