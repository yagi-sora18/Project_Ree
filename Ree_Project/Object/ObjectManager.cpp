#include "ObjectManager.h"
#include <fstream>
#include <vector>
#include <algorithm>

// �V���O���g���C���X�^���X�̒�`
GameDataManager& GameDataManager::GetInstance() {
    static GameDataManager instance;
    return instance;
}

// �Q�b�^�[
int GameDataManager::GetCorrect() const {
    return correct;
}

int GameDataManager::GetSales() const {
    return sales;
}

// �Z�b�^�[
void GameDataManager::SetCorrect(int value) {
    correct = value;
}

void GameDataManager::SetSales(int value) {
    sales = value;
}

// �X�R�A���t�@�C���ɕۑ����A�����L���O���X�V����
void GameDataManager::SaveScoreToFile(const std::string& filename) {
    std::vector<std::pair<int, int>> scores;

    // �����X�R�A�ǂݍ���
    std::ifstream inFile(filename);
    int c, s;
    while (inFile >> c >> s) {
        scores.emplace_back(c, s);
    }
    inFile.close();

    // ���݂̃X�R�A��ǉ�
    scores.emplace_back(correct, sales);

    // correct + sales �̍��v�ō~���Ƀ\�[�g
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return (a.first + a.second) > (b.first + b.second);
        });

    // ���3�������c��
    if (scores.size() > 3) {
        scores.resize(3);
    }

    // �t�@�C���ɕۑ�
    std::ofstream outFile(filename, std::ios::trunc);
    for (const auto& score : scores) {
        outFile << score.first << " " << score.second << std::endl;
    }
    outFile.close();
}
