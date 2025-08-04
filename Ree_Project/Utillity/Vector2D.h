#pragma once
//�񎟌��x�N�g���N���X
class Vector2D
{
public:

	float x;//X���W
	float y;//Y���W


public:

	//�R���X�g���N�^
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);

	//�f�X�g���N�^
	~Vector2D();


public:
	//���Z�q�̃I�[�o�[���[�h
	//������Z�q
	Vector2D& operator=(const Vector2D& location);

	//���Z
	const Vector2D operator+(const Vector2D& location)const;
	Vector2D& operator+=(const Vector2D& location);
	//���Z
	const Vector2D operator-(const Vector2D& location)const;
	Vector2D& operator-=(const Vector2D& location);

	//��Z
	const Vector2D operator*(const float& scalar)const;
	const Vector2D operator*(const Vector2D& location)const;
	Vector2D& operator*=(const float& scalar);
	Vector2D& operator*=(const Vector2D& location);

	//���Z
	const Vector2D operator/(const float& scalar)const;
	const Vector2D operator/(const Vector2D& location)const;
	Vector2D& operator/=(const float& scalar);
	Vector2D& operator/=(const Vector2D& location);

	//������𐮐��l�ɕϊ�
	void ToInt(int* x, int* y)const;

};


