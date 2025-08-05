#pragma once

#include "../Utillity/Vector2D.h"
#include "../Object/Object.h"
#include <vector>

// �V�[���̎��
enum class eSceneType
{
	eTitle,					// �^�C�g�����
	eTutorial,				// �`���[�g���A�����
	eInGame,				// �C���Q�[�����
	eResult,				// ���U���g���
	eRanking,				// �����L���O���
	eEnd,					// �G���h���
	eCredit,				//�N���W�b�g���
};

// ���V�[���N���X
// �C���^�[�t�F�[�X�N���X
class SceneBase
{
protected:
	// �Q�[���I�u�W�F�N�g�̓��I�z��
	std::vector<Object*> objects;
	int background_image;

public:
	SceneBase();
	virtual ~SceneBase();

public:
	virtual void Initialize();
	virtual eSceneType Update();
	virtual void Draw() const;
	virtual void Finalize();

public:
	// �������z�֐�
	// ���݂̃V�[����Ԃ�
	virtual eSceneType GetNowSceneType() const = 0;

protected:
	// �Q�[���I�u�W�F�N�g�̐���
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		T* new_instance = new T();

		// new_instance��GameObject���p�����Ă���̂��`�F�b�N
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		// �L���X�g�Ɏ��s������
		if (new_object == nullptr)
		{
			delete new_object;
			throw("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
		}

		// �Q�[���I�u�W�F�N�g�̐��������W��ݒ�
		new_object->SetLocation(location);

		// �Q�[���I�u�W�F�N�g�̏�����
		new_object->Initialize();

		// objects�̖����ɃQ�[���I�u�W�F�N�g��ǉ�
		objects.push_back(new_object);

		// �C���X�^���X��ԋp
		return new_instance;
	}

	void DestroyObject(Object* target);
};