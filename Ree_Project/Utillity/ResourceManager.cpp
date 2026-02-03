#include "ResourceManager.h"

int ResourceManager::LoadImage(const std::string& path)
{
    auto it = images_.find(path);
    if (it != images_.end())
    {
        return it->second;
    }

    int h = LoadGraph(path.c_str());
    if (h == -1) 
    {
        //読み込み失敗したら 0 を返す
        return 0;
    }
    images_[path] = h;
    return h;
}

int ResourceManager::GetImage(const std::string& path) const
{
    auto it = images_.find(path);
    if (it != images_.end())
    {
        return it->second;
    }
    return 0;
}

//アニメ用画像

const std::vector<int>& ResourceManager::LoadAnimImages(
    const std::string& key,
    const std::vector<std::string>& paths)
{
    auto it = anim_images_.find(key);
    if (it != anim_images_.end())
    {
        return it->second;
    }

    std::vector<int> handles;
    handles.reserve(paths.size());

    for (const auto& p : paths)
    {
        int h = LoadGraph(p.c_str());
        if (h == -1)
        {
            // 失敗したらダミーとして 0 を入れておく
            handles.push_back(0);
        }
        else
        {
            handles.push_back(h);
        }
    }

    auto inserted = anim_images_.emplace(key, std::move(handles));
    return inserted.first->second;
}

const std::vector<int>& ResourceManager::GetAnimImages(const std::string& key) const
{
    static const std::vector<int> empty; // 見つからなかったとき用
    auto it = anim_images_.find(key);
    if (it != anim_images_.end())
    {
        return it->second;
    }
    return empty;
}

// ---------- サウンド（今はおまけ） ----------

int ResourceManager::LoadSound(const std::string& path)
{
    auto it = sounds_.find(path);
    if (it != sounds_.end())
    {
        return it->second;
    }

    int h = LoadSoundMem(path.c_str());
    if (h == -1)
    {
        return 0;
    }
    sounds_[path] = h;
    return h;
}

int ResourceManager::GetSound(const std::string& path) const
{
    auto it = sounds_.find(path);
    if (it != sounds_.end())
    {
        return it->second;
    }
    return 0;
}

//解放する処理

void ResourceManager::ReleaseAll()
{
    // 画像
    for (auto& kv : images_)
    {
        if (kv.second != 0)
        {
            DeleteGraph(kv.second);
        }
    }
    images_.clear();

    for (auto& kv : anim_images_)
    {
        for (int h : kv.second)
        {
            if (h != 0)
            {
                DeleteGraph(h);
            }
        }
    }
    anim_images_.clear();

    // サウンド
    for (auto& kv : sounds_)
    {
        if (kv.second != 0)
        {
            DeleteSoundMem(kv.second);
        }
    }
    sounds_.clear();
}

ResourceManager::~ResourceManager()
{
    ReleaseAll();
}
