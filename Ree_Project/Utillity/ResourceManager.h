#pragma once
#include <map>
#include <string>
#include <vector>
#include <DxLib.h>
#include "SingleTon.h"

// リソース管理（画像・アニメ・サウンド）
class ResourceManager : public Singleton<ResourceManager> {
    friend class Singleton<ResourceManager>;

public:
    // 単一画像のロード（同じパスは使い回し）
    int LoadImage(const std::string& path);

    // アニメ用画像のロード（複数ファイルをまとめて 1 セットとして扱う）
    // 例: key = "coin_spin", paths = { "Coin_0.png", ... }
    const std::vector<int>& LoadAnimImages(
        const std::string& key,
        const std::vector<std::string>& paths
    );

    // 取得系
    int GetImage(const std::string& path) const;                      // 単一
    const std::vector<int>& GetAnimImages(const std::string& key) const; // アニメ

    // サウンドも使いたくなった時用（今は予備）
    int LoadSound(const std::string& path);
    int GetSound(const std::string& path) const;

    // 明示解放したい時（DxLib 終了前など）に呼ぶ
    void ReleaseAll();

private:
    ResourceManager() = default;
    ~ResourceManager(); // ReleaseAll を呼ぶだけ

    std::map<std::string, int> images_;                  // path → handle
    std::map<std::string, std::vector<int>> anim_images_; // key  → [handle...]
    std::map<std::string, int> sounds_;                  // path → handle
};
