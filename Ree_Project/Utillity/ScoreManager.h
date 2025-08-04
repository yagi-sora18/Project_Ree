#pragma once

class ScoreManager
{
public:
	static ScoreManager* GetInstance();
	void AddScore(int value);
	int GetScore() const;


private:
	int score_;
	ScoreManager();
};
