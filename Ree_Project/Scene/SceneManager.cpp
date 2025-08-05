#include "SceneManager.h"

#include "TitleScene.h"
#include "TutorialScene.h"
#include "InGameScene.h"
#include "RankingScene.h"
#include "ResultScene.h"
#include "EndScene.h"
#include "CreditScene.h"

SceneManager::SceneManager()
	: current_scene(nullptr)
	, loop_flag(true)
{

}

SceneManager::~SceneManager()
{
	// ���g�̏I���������Ă�
	this->Finalize();
}

void SceneManager::Initialize()
{
	/*SceneManager���������ꂽ�Ƃ���Scene�i�Q�[���J�n����Scene�j*/
	ChangeScene(eSceneType::eResult);
}

void SceneManager::Update()
{
	// �V�[���̍X�V����
	// current_scene��Update�ŕԂ��ꂽ�V�[���^�C�v����
	// �i���ɏ������s���V�[���^�C�v��ێ��j
	eSceneType next_scene_type = current_scene->Update();

	// �V�[���̕`�揈��
	current_scene->Draw();

	if (next_scene_type != current_scene->GetNowSceneType())
	{
		// �V�[���ύX
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Finalize()
{
	if (current_scene != nullptr)
	{
		// current_scene�̏I������
		current_scene->Finalize();

		// current_scene���m�ۂ��������������
		delete current_scene;
		// current_scene�̃|�C���^�𖳌���
		current_scene = nullptr;
	}
}

bool SceneManager::LoopCheck() const
{
	return loop_flag;
}

// �V�[���؂�ւ�����
void SceneManager::ChangeScene(eSceneType new_scene_type)
{
	/*if (new_scene_type == eSceneType::eEnd)
	{
		// �Q�[�����[�v���I��������
		loop_flag = false;
		return;
	}*/

	// �V�[���̐����ŕԂ��Ă����|�C���^��new_scene�ɑ��
	SceneBase* new_scene = CreateScene(new_scene_type);

	// ���CreateScene(new_scene_type)�ŃL���X�g�����s�����ꍇ
	if (new_scene == nullptr)
	{
		throw("\n�V�����V�[���̐������ł��܂���ł���\n");
	}

	if (current_scene != nullptr)
	{
		// current_scene�̏I������
		current_scene->Finalize();

		// current_scene���m�ۂ��������������
		delete current_scene;
	}

	// �V����Scene�̏������֐�
	new_scene->Initialize();

	current_scene = new_scene;
}

// �V�[���̐���
SceneBase* SceneManager::CreateScene(eSceneType new_scene_type)
{
	// dynamic_cast�ŁA��������Scene��SceneBase���p�����Ă��邩�`�F�b�N
	// ��������Scene�̃|�C���^��Ԃ�
	switch (new_scene_type)
	{
	case eSceneType::eTitle:
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::eInGame:
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::eTutorial:
		return dynamic_cast<SceneBase*>(new TutorialScene());
	case eSceneType::eRanking:
		return dynamic_cast<SceneBase*>(new RankingScene());
	case eSceneType::eResult:
		return dynamic_cast<SceneBase*>(new ResultScene());
	case eSceneType::eEnd:
		return dynamic_cast<SceneBase*>(new EndScene());
	case eSceneType::eCredit:
		return dynamic_cast<SceneBase*>(new CreditScene());
	default:
		return nullptr;
	}
}
