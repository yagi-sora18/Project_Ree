#pragma once
#include "../Object.h"


class Platform : public Object {
public:
	Platform(float x, float y, float w, float h)
		: Object(x, y, w, h) {
		collision.object_type = ePlatform;
	}
	void Update(float) override {}
	//void Draw(int camera_y) override;
	void Draw(int camera_x, int camera_y)override;
};