#pragma once

#include "../Utillity/Vector2D.h"

class GameObject
{
protected:
	Vector2D location;			// ���W
	int graphic_images;			// �`�悷��摜
	int flip_flag;				// �摜���]�t���O
	bool delete_flag;			// �폜�t���O

public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Draw() const;
	virtual void Finalize();

public:
	// ���W���擾
	const Vector2D& GetLocation() const
	{
		return location;
	}
	// ���W��ݒ�
	void SetLocation(const Vector2D& location)
	{
		this->location = location;
	}
	// �폜�t���O���擾
	const bool GetDeleteFlag() const
	{
		return delete_flag;
	}
};