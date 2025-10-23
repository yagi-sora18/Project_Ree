#pragma once
#include <vector>
#include <algorithm>
#include "Object.h"


class ObjectManager {
public:
	~ObjectManager();


	void Add(Object* obj) { if (obj) objects.push_back(obj); }
	void ClearAll();


	void UpdateAll(float dt);
	//void DrawAll(int camera_y);
	//void DrawAll(int camera_x, int camera_y);
	void DrawAll(int camera_x, int camera_y, int off_x, int off_y);


	const std::vector<Object*>& GetObjects() const { return objects; }


	// スコア（簡易）
	void AddScore(int s) { score += s; }
	int GetScore() const { return score; }


private:
	std::vector<Object*> objects;
	int score{ 0 };
};