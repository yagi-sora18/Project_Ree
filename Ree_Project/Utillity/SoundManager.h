#pragma once
#include <string>
#include <DxLib.h>
#include "SingleTon.h"
#include "ResourceManager.h"

class SoundManager : public Singleton<SoundManager>
{
        friend class Singleton<SoundManager>;

    public:
        void SetBgmVolume(int volume);
        void SetSeVolume(int volume);

        void PlayBgm(const std::string& path);
        void StopBgm();

        void PlaySe(const std::string& path);
        void PlaySeLoop(const std::string& path);
        void StopSe(const std::string& path);

    private:
        SoundManager() = default;
        ~SoundManager() = default;

    private:
        std::string nowBgmPath;
        int nowBgmHandle = 0;

        int bgmVolume = 200; // 0..255
        int seVolume = 255;  // 0..255
};
