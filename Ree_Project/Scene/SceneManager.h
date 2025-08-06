#pragma once

#include "../Utillity/SingleTone.h"
#include "SceneBase.h"

// �V�[���̐����E�؂�ւ��E�Ǘ��N���X
class SceneManager : public Singleton<SceneManager>
{
private:
	SceneBase* current_scene;

public:
	SceneManager();
	~SceneManager();

	void Initialize();
	bool Update(float delta_second);
	void Draw();
	void Finalize();

	void ChangeScene(eSceneType scene_type);

private:
	SceneBase* CreateScene(eSceneType scene_type);
};
