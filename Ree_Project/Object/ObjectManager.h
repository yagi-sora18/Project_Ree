#pragma once
#include <string>

class GameDataManager {
private:
    int correct = 0;  // �ڋq��
    int sales = 0;    // ����

    // �R���X�g���N�^��private�ɂ��ăV���O���g���ɂ���
    GameDataManager() {}

public:
    // �V���O���g���C���X�^���X�擾
    static GameDataManager& GetInstance();

    // �Q�b�^�[
    int GetCorrect() const;
    int GetSales() const;

    // �Z�b�^�[
    void SetCorrect(int value);
    void SetSales(int value);

    // �X�R�A�icorrect��sales�j���t�@�C���ɕۑ�����
    void SaveScoreToFile(const std::string& filename);

    // �R�s�[�֎~
    GameDataManager(const GameDataManager&) = delete;
    GameDataManager& operator=(const GameDataManager&) = delete;
};
