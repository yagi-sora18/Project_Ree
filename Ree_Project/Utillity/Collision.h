#pragma once
#include "Vector2D.h"


enum EObjectType {
	eUnknown = 0,
	ePlayer,
	ePlatform,
	eCoin,
	eWall,
};


struct Collision {
	Vector2D pivot; // ���S(�܂��͔C�Ӄs�{�b�g)
	Vector2D box_size; // ����
	Vector2D point[2]; // ����[0], �E��[1]
	EObjectType object_type{ eUnknown };


	static bool IsCheckHitCollision(const Collision& a, const Collision& b);
};


// �֗�AABB�ipoint�x�[�X�j
inline bool IsCheckCollision(const Collision& a, const Collision& b) {
	return !(a.point[1].x <= b.point[0].x || a.point[0].x >= b.point[1].x ||
		a.point[1].y <= b.point[0].y || a.point[0].y >= b.point[1].y);
}