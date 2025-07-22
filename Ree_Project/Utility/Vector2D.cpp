#include "Vector2D.h"
#include<math.h>

//コンストラクタ
Vector2D::Vector2D() :x(0.0f), y(0.0f) //初期化リスト
{
}

Vector2D::Vector2D(float scalar) :x(scalar), y(scalar)
{
}


Vector2D::Vector2D(float mx, float my) :x(mx), y(my)
{

}

//デストラクタ
Vector2D::~Vector2D()
{

}

//位置情報を代入する
Vector2D& Vector2D::operator=(const Vector2D& location)
{
	this->x = location.x;
	this->y = location.y;

	//自分自身を返す
	return *this;
}


//位置情報を加算する
const Vector2D Vector2D::operator+(const Vector2D& location)const
{

	Vector2D result = Vector2D(0.0f);
	result.x = this->x + location.x;
	result.y = this->y + location.y;

	//結果を返す
	return result;
}


Vector2D& Vector2D::operator+=(const Vector2D& location)
{
	this->x += location.x;
	this->y += location.y;

	//自分自身を返す
	return *this;
}

const Vector2D Vector2D::operator-(const Vector2D& location)const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x - location.x;
	result.y = this->y - location.y;

	return result;
}

//位置情報を減算する
Vector2D& Vector2D::operator-=(const Vector2D& location)
{

	this->x -= location.x;
	this->y -= location.y;

	return*this;
}


//円の面積の情報を乗算する
const Vector2D Vector2D::operator*(const float& scalar)const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * scalar;
	result.y = this->y * scalar;

	return result;
}

//位置情報を乗算する
const Vector2D Vector2D::operator*(const Vector2D& location)const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * location.x;
	result.y = this->y * location.y;

	return result;
}


Vector2D& Vector2D::operator*=(const Vector2D& location)
{
	this->x *= location.x;
	this->y *= location.y;

	return *this;

}

//円の面積を除算する
const Vector2D Vector2D::operator/(const float& scalar) const
{
	if (fabsf(scalar) < 1e-6f)
	{
		return Vector2D(0.0f);
	}
	return Vector2D(this->x / scalar, this->y / scalar);
}




const Vector2D Vector2D::operator/(const Vector2D& location) const
{
	if ((fabsf(location.x) < 1e-6f) || (fabsf(location.y) < 1e-6f))
	{
		return Vector2D(0.0f);
	}
	return Vector2D(this->x / location.x, this->y / location.y);
}




Vector2D& Vector2D::operator/=(const float& scalar)
{
	if (fabsf(scalar) < 1e-6f)
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= scalar;
		this->y /= scalar;
	}

	return *this;
}




Vector2D& Vector2D::operator/=(const Vector2D& location)
{
	if ((fabsf(location.x) < 1e-6f) || (fabsf(location.y) < 1e-6f))
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= location.x;
		this->y /= location.y;
	}
	return *this;
}

//文字列を整数値に変換して整数を返す
void Vector2D::ToInt(int* x, int* y)const
{
	*x = static_cast<int>(this->x);
	*y = static_cast<int>(this->y);
}
