#pragma once
#include "Vector2D.h"
#include<vector>

enum eObjectType
{
	eBullet,
	eCastle,
	ePlayer,
	eEnemy,
	eBulletAim
};

enum eSide
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

class Collision
{
public:
	Vector2D box_size;
	Vector2D pivot;
	Vector2D point[2];
	eObjectType object_type;
	std::vector<eObjectType> hit_object_type;

	bool IsCheckHitTarget(eObjectType object_type) const;
	bool IsCheckHitCollision(Collision target1, Collision target2);
};
bool IsCheckCollision(const Collision& c1, const Collision& c2);


