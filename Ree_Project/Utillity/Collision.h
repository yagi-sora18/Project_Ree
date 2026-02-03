#pragma once
#include "Vector2D.h"


enum EObjectType {
	eUnknown = 0,
	ePlayer,
	ePlatform,
	eCoin,
	eWall,
	eGoal,
};


struct Collision
{
	Vector2D pivot; // 中心(または任意ピボット)
	Vector2D box_size; // 幅高
	Vector2D point[2]; // 左上[0], 右下[1]
	EObjectType object_type{ eUnknown };

	static bool IsCheckHitCollision(const Collision& a, const Collision& b);
};


//当たり判定
inline bool IsCheckCollision(const Collision& a, const Collision& b)
{
	return !(a.point[1].x <= b.point[0].x || a.point[0].x >= b.point[1].x ||
			a.point[1].y <= b.point[0].y || a.point[0].y >= b.point[1].y);
}