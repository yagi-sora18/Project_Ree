#include "SceneManager.h"
#include "Title.h"
#include "InGame.h"
#include "Result.h"


SceneManager::SceneManager() { ChangeScene(eSceneType::eTitle); }
SceneManager::~SceneManager() = default;


void SceneManager::Update(float dt) {
	scene->Update(dt);
	if (scene->Next() != eSceneType::eTitle &&
		scene->Next() != eSceneType::eInGame &&
		scene->Next() != eSceneType::eResult) return; // ���S


	if (scene->Next() != eSceneType::eTitle &&
		scene->Next() != eSceneType::eInGame &&
		scene->Next() != eSceneType::eResult) return;


	if (scene->Next() != eSceneType::eTitle) {}
	// �V�[���J��
	if (scene->Next() != eSceneType::eTitle) {}
	if (scene->Next() != eSceneType::eInGame) {}


	// �P�����F���t���[���`�F�b�N���ĕς���Ă�����ؑ�
	static eSceneType last = eSceneType::eTitle;
	eSceneType cur = scene->Next();
	if (cur != last) { ChangeScene(cur); last = cur; }
}


void SceneManager::Draw() { scene->Draw(); }


void SceneManager::ChangeScene(eSceneType to) {
	switch (to) {
	case eSceneType::eTitle: scene.reset(new Title()); break;
	case eSceneType::eInGame: scene.reset(new InGame()); break;
	case eSceneType::eResult: scene.reset(new Result()); break;
	}
	scene->Initialize();
}