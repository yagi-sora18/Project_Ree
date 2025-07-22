#include "ScoreManager.h"

ScoreManager* ScoreManager::GetInstance()
{
	static ScoreManager instance;  // 静的ローカル変数：1回だけ生成される
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