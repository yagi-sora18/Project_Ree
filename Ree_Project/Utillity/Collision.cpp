#include "Collision.h"
#include <cmath>


bool Collision::IsCheckHitCollision(const Collision& a, const Collision& b) {
	Vector2D distance{ std::fabs(a.pivot.x - b.pivot.x), std::fabs(a.pivot.y - b.pivot.y) };
	Vector2D size{ (a.box_size.x + b.box_size.x) * 0.5f, (a.box_size.y + b.box_size.y) * 0.5f };
	return (distance.x <= size.x && distance.y <= size.y);
}