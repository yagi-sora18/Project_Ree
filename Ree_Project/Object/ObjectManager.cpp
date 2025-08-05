#include "ObjectManager.h"
#include <fstream>
#include <vector>
#include <algorithm>

// シングルトンインスタンスの定義
GameDataManager& GameDataManager::GetInstance() {
    static GameDataManager instance;
    return instance;
}

// ゲッター
int GameDataManager::GetCorrect() const {
    return correct;
}

int GameDataManager::GetSales() const {
    return sales;
}

// セッター
void GameDataManager::SetCorrect(int value) {
    correct = value;
}

void GameDataManager::SetSales(int value) {
    sales = value;
}

// スコアをファイルに保存し、ランキングを更新する
void GameDataManager::SaveScoreToFile(const std::string& filename) {
    std::vector<std::pair<int, int>> scores;

    // 既存スコア読み込み
    std::ifstream inFile(filename);
    int c, s;
    while (inFile >> c >> s) {
        scores.emplace_back(c, s);
    }
    inFile.close();

    // 現在のスコアを追加
    scores.emplace_back(correct, sales);

    // correct + sales の合計で降順にソート
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return (a.first + a.second) > (b.first + b.second);
        });

    // 上位3件だけ残す
    if (scores.size() > 3) {
        scores.resize(3);
    }

    // ファイルに保存
    std::ofstream outFile(filename, std::ios::trunc);
    for (const auto& score : scores) {
        outFile << score.first << " " << score.second << std::endl;
    }
    outFile.close();
}
