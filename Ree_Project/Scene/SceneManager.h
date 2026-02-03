#pragma once
#include "SceneBase.h"
#include <memory>


class SceneManager
{
	public:
		SceneManager();
		~SceneManager();


		void Update(float dt);
		void Draw();


	private:
		void ChangeScene(eSceneType to);
		std::unique_ptr<SceneBase> scene;
};