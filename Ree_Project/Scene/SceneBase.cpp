#include "SceneBase.h"

#include "DxLib.h"

SceneBase::SceneBase() : background_image(NULL)
{

}

SceneBase::~SceneBase()
{
	// �I������
	this->Finalize();
}

void SceneBase::Initialize()
{

}

eSceneType SceneBase::Update()
{
	// �͈�for����objects�̗v�f�����Ԃ�obj�ɑ��
	for (Object* obj : objects)
	{
		// �I�u�W�F�N�g�̍X�V����
		obj->Update();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetDeleteFlag())
		{
			// �I������
			objects[i]->Finalize();
			// �폜
			objects.erase(objects.begin() + i);
		}
	}

	// ���݂̃V�[����Ԃ�
	return GetNowSceneType();
}

void SceneBase::Draw() const
{

	//DrawBox(1080, 550, 1250, 700, 0x000000, TRUE);

	// �͈�for����objects�̗v�f�����Ԃ�obj�ɑ��
	for (Object* obj : objects)
	{
		// �I�u�W�F�N�g�̕`�揈��
		obj->Draw();
	}
}

void SceneBase::Finalize()
{
	// objects�̗v�f���󂾂�����
	if (objects.empty())
	{
		return;
	}

	// �͈�for����objects�̗v�f�����Ԃ�obj�ɑ��
	for (Object* obj : objects)
	{
		// �I�u�W�F�N�g�̏I������
		obj->Finalize();
		delete obj;
	}

	// objects�̗v�f�����ׂč폜
	objects.clear();
}

void SceneBase::DestroyObject(Object* target)
{
}
