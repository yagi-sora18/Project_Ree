#pragma once

#include "SceneBase.h"

// �V�[���Ǘ��N���X
class SceneManager
{
private:
	// ���݂̃V�[��
	SceneBase* current_scene;
	// �Q�[�����[�v���s�����̃t���O
	bool loop_flag;

public:
	SceneManager();
	~SceneManager();

public:
	void Initialize();
	void Update();
	void Finalize();

public:
	// �Q�[�����[�v���s�������ׂ鏈��
	bool LoopCheck() const;

private:
	// �V�[���؂�ւ�����
	void ChangeScene(eSceneType new_scene_type);
	// �V�[����������
	SceneBase* CreateScene(eSceneType new_scene_type);
};