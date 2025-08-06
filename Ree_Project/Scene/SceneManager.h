#pragma once

#include "../Utillity/SingleTone.h"
#include "SceneBase.h"

// シーンの生成・切り替え・管理クラス
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
