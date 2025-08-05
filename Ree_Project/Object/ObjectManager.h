#pragma once
#include <string>

class GameDataManager {
private:
    int correct = 0;  // 接客数
    int sales = 0;    // 売上

    // コンストラクタをprivateにしてシングルトンにする
    GameDataManager() {}

public:
    // シングルトンインスタンス取得
    static GameDataManager& GetInstance();

    // ゲッター
    int GetCorrect() const;
    int GetSales() const;

    // セッター
    void SetCorrect(int value);
    void SetSales(int value);

    // スコア（correctとsales）をファイルに保存する
    void SaveScoreToFile(const std::string& filename);

    // コピー禁止
    GameDataManager(const GameDataManager&) = delete;
    GameDataManager& operator=(const GameDataManager&) = delete;
};
