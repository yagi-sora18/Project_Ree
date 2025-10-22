#include "Vector2D.h"


Vector2D& Vector2D::operator*=(const float& s) {
	x *= s; y *= s; return *this;
}