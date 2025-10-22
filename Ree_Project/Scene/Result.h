#pragma once
#include "SceneBase.h"


class Result : public SceneBase {
public:
	void Initialize() override {}
	void Update(float dt) override;
	void Draw() override;
	eSceneType Next() const override { return next; }
private:
	eSceneType next{ eSceneType::eResult };
};