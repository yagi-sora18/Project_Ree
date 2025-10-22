#pragma once


enum class eSceneType { eTitle, eInGame, eResult };


class SceneBase {
public:
	virtual ~SceneBase() = default;
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual eSceneType Next() const = 0;
};