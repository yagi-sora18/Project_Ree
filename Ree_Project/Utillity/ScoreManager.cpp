#include "ScoreManager.h"

ScoreManager* ScoreManager::GetInstance()
{
	static ScoreManager instance;  // �ÓI���[�J���ϐ��F1�񂾂����������
	return &instance;
}

ScoreManager::ScoreManager() : score_(0) {}

void ScoreManager::AddScore(int value)
{
	score_ += value;
}

int ScoreManager::GetScore() const
{
	return score_;
}