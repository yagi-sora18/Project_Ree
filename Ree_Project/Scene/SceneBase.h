#pragma once

#include "DxLib.h"
#include "../Utillity/InputControl.h"
#include "../Utillity/ResourceManager.h"

// �V�[���̎��
enum class eSceneType
{
	eTitle,
	eInGame,
	eRanking,
	eCredit,
	eResult
};

// �V�[�����N���X
class SceneBase
{
public:
	// ����������
	virtual void Initialize() {}

	// �X�V�����i���̃V�[���^�C�v��Ԃ��j
	virtual eSceneType Update(float delta_second)
	{
		return GetNowSceneType();
	}

	// �`�揈��
	virtual void Draw() {}

	// �I��������
	virtual void Finalize() {}

	// ���݂̃V�[���^�C�v��Ԃ��i�������z�֐��j
	virtual eSceneType GetNowSceneType() const = 0;

	virtual ~SceneBase() {}
};
