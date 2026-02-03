#pragma once
#include "../Utillity/Vector2D.h"
#include "../Utillity/Collision.h"


class Object
{
	public:
		Object(float x, float y, float w, float h) : pos(x, y), width(w), height(h)
		{
			UpdateCollision();
		}
		virtual ~Object() = default;


		virtual void Update(float dt) {}
		virtual void Draw(int camera_x, int camera_y, int off_x, int off_y) {}


		bool IsActive() const { return active; }
		void SetActive(bool a) { active = a; }


		void UpdateCollision()
		{
			collision.point[0] = { pos.x, pos.y };
			collision.point[1] = { pos.x + width, pos.y + height };
			collision.pivot = { pos.x + width * 0.5f, pos.y + height * 0.5f };
			collision.box_size = { width, height };
		}
	public:
		Vector2D pos;
		float width{ 0 }, height{ 0 };
		Collision collision;
	protected:
		bool active{ true };
};