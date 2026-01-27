#pragma once
#include "SingleTon.h"

// DxLib ‚Ì GetHitKeyStateAll ‚Í char* ‚ğ—v‹‚·‚é‚Ì‚ÅA”z—ñ‚Í char Œ^‚Å‚Â
class InputControl : public Singleton<InputControl> {
    friend class Singleton<InputControl>;
public:
    void Update();
    bool GetKey(int code) const { return now_key[code] != 0; }
    bool GetKeyDown(int code) const { return now_key[code] && !old_key[code]; }
    bool GetKeyUp(int code) const { return !now_key[code] && old_key[code]; }

private:
    InputControl() : now_key{}, old_key{} {}

    char now_key[256];
    char old_key[256];
};
