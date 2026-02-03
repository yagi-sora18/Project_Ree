#pragma once
class ScoreManager
{
	public:
		void Reset() { score = 0; }
		void Add(int s) { score += s; }
		int Get() const { return score; }
	private:
		int score{ 0 };
};