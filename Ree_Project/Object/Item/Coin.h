#pragma once
#include "../Object.h"


class Coin : public Object
{
	public:
		bool collected{ false };
		Coin(float x, float y, float w = 20.0f, float h = 20.0f)
			: Object(x, y, w, h)
		{
			collision.object_type = eCoin;
		}
		void Update(float dt) override;
		void Draw(int camera_x, int camera_y, int off_x, int off_y) override;

};