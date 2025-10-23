#pragma once
#include "../Object.h"


class Wall : public Object {
public:
	Wall(float x, float y, float w, float h) : Object(x, y, w, h) {
		collision.object_type = eWall;
	}
	void Update(float) override { /* �ÓI�Ȃ牽�����Ȃ� */ }
	//void Draw(int camera_y) override;
	//void Draw(int camera_x, int camera_y) override;
	void Draw(int camera_x, int camera_y, int off_x, int off_y) override;

};