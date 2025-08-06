#include "SceneManager.h"
#include "DxLib.h"

// �e�V�[���̃C���N���[�h
#include "Title.h"
#include "InGame.h"
#include "Result.h"
#include "../Utillity/InputControl.h"

SceneManager::SceneManager() : current_scene(nullptr) {}

SceneManager::~SceneManager() {}

void SceneManager::Initialize()
{
	// �������ōŏ��̃V�[�����w�肵�Ă�OK
}

bool SceneManager::Update(float delta_second)
{
	// ���͍X�V
	InputControl* input = Singleton<InputControl>::GetInstance();
	InputControl::GetInstance()->Update(); // ���t���[�����ꂪ�K�v


	// ���݂̃V�[���̍X�V
	eSceneType next_type = current_scene->Update(delta_second);

	// �V�[���؂�ւ�����
	if (current_scene->GetNowSceneType() != next_type)
	{
		ChangeScene(next_type);
	}

	// ESC�L�[�ŏI������
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		// �U�� & �ҋ@�i�C�Ӂj
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

	Singleton<InputControl>::DeleteInstance(); // Singleton ����Ăяo��
}

void SceneManager::ChangeScene(eSceneType type)
{
	SceneBase* new_scene = CreateScene(type);

	if (new_scene == nullptr)
	{
		throw("�V�[�������Ɏ��s���܂���");
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
		// ���̃V�[���ǉ��\��Ȃ炱���ɋL�q
	default:
		return nullptr;
	}
}
