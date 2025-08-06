#include "SceneManager.h"
#include "DxLib.h"

// 各シーンのインクルード
#include "Title.h"
#include "InGame.h"
#include "Result.h"
#include "../Utillity/InputControl.h"

SceneManager::SceneManager() : current_scene(nullptr) {}

SceneManager::~SceneManager() {}

void SceneManager::Initialize()
{
	// 初期化で最初のシーンを指定してもOK
}

bool SceneManager::Update(float delta_second)
{
	// 入力更新
	InputControl* input = Singleton<InputControl>::GetInstance();
	InputControl::GetInstance()->Update(); // 毎フレームこれが必要


	// 現在のシーンの更新
	eSceneType next_type = current_scene->Update(delta_second);

	// シーン切り替え判定
	if (current_scene->GetNowSceneType() != next_type)
	{
		ChangeScene(next_type);
	}

	// ESCキーで終了する
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		// 振動 & 待機（任意）
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000, -1);
		WaitTimer(1000);
		return true;
	}

	return false;
}

void SceneManager::Draw()
{
	if (current_scene) {
		current_scene->Draw();
	}
}

void SceneManager::Finalize()
{
	if (current_scene)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	Singleton<InputControl>::DeleteInstance(); // Singleton から呼び出す
}

void SceneManager::ChangeScene(eSceneType type)
{
	SceneBase* new_scene = CreateScene(type);

	if (new_scene == nullptr)
	{
		throw("シーン生成に失敗しました");
	}

	if (current_scene)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(eSceneType type)
{
	switch (type)
	{
	case eSceneType::eTitle:
		return new Title();
	case eSceneType::eInGame:
		return new InGame();
	case eSceneType::eResult:
		return new Result();
		// 他のシーン追加予定ならここに記述
	default:
		return nullptr;
	}
}
