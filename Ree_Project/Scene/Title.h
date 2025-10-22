#pragma once
#include "SceneBase.h"


class Title : public SceneBase {
public:
	void Initialize() override {}
	void Update(float dt) override;
	void Draw() override;
	eSceneType Next() const override { return next; }
private:
	eSceneType next{ eSceneType::eTitle };
};