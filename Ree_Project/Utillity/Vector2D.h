#pragma once
#include <cmath>


struct Vector2D {
	float x{ 0.0f };
	float y{ 0.0f };


	Vector2D() = default;
	Vector2D(float _x, float _y) : x(_x), y(_y) {}


	Vector2D operator+(const Vector2D& o) const { return { x + o.x, y + o.y }; }
	Vector2D operator-(const Vector2D& o) const { return { x - o.x, y - o.y }; }
	Vector2D operator*(float s) const { return { x * s, y * s }; }
	Vector2D& operator+=(const Vector2D& o) { x += o.x; y += o.y; return *this; }
	Vector2D& operator-=(const Vector2D& o) { x -= o.x; y -= o.y; return *this; }
	Vector2D& operator*=(const float& s);
};