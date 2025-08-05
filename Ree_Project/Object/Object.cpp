#include "Object.h"
#include "DxLib.h"

GameObject::GameObject()
	: location(0.0f)
	, graphic_images(NULL)
	, flip_flag(false)
	, delete_flag(false)
{

}

GameObject::~GameObject()
{
	// Ž©g‚ÌI—¹ˆ—
	this->Finalize();
}

void GameObject::Initialize()
{

}

void GameObject::Update()
{

}

void GameObject::Draw() const
{
	// ‰æ‘œ•`‰æ
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, graphic_images, TRUE, flip_flag);
}

void GameObject::Finalize()
{

}
