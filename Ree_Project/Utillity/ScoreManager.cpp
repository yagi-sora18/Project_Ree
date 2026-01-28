#include "SoundManager.h"

static int ClampVolume(int v)
{
    if (v < 0) return 0;
    if (v > 255) return 255;
    return v;
}

void SoundManager::SetBgmVolume(int volume)
{
    bgmVolume = ClampVolume(volume);

    if (nowBgmHandle != 0) {
        ChangeVolumeSoundMem(bgmVolume, nowBgmHandle);
    }
}

void SoundManager::SetSeVolume(int volume)
{
    seVolume = ClampVolume(volume);
}

void SoundManager::PlayBgm(const std::string& path)
{
    if (path.empty()) return;

    // “¯‚¶BGM‚È‚ç‰½‚à‚µ‚È‚¢
    if (nowBgmPath == path && nowBgmHandle != 0) return;

    StopBgm();

    int handle = ResourceManager::GetInstance()->LoadSound(path);
    if (handle == 0) return;

    nowBgmPath = path;
    nowBgmHandle = handle;

    ChangeVolumeSoundMem(bgmVolume, nowBgmHandle);
    PlaySoundMem(nowBgmHandle, DX_PLAYTYPE_LOOP, TRUE);
}

void SoundManager::StopBgm()
{
    if (nowBgmHandle != 0) {
        StopSoundMem(nowBgmHandle);
    }
    nowBgmHandle = 0;
    nowBgmPath.clear();
}

void SoundManager::PlaySe(const std::string& path)
{
    if (path.empty()) return;

    int handle = ResourceManager::GetInstance()->LoadSound(path);
    if (handle == 0) return;

    ChangeVolumeSoundMem(seVolume, handle);
    PlaySoundMem(handle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlaySeLoop(const std::string& path)
{
    if (path.empty()) return;

    int handle = ResourceManager::GetInstance()->LoadSound(path);
    if (handle == 0) return;

    ChangeVolumeSoundMem(seVolume, handle);
    PlaySoundMem(handle, DX_PLAYTYPE_LOOP, FALSE); // ‚·‚Å‚É–Â‚Á‚Ä‚½‚ç‚»‚Ì‚Ü‚Ü
}

void SoundManager::StopSe(const std::string& path)
{
    if (path.empty()) return;

    int handle = ResourceManager::GetInstance()->GetSound(path);
    if (handle == 0) return;

    StopSoundMem(handle);
}
