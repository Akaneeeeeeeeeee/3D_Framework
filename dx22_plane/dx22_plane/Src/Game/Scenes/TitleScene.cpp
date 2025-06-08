#include "TitleScene.h"
#include "../Game.h"
#include "../../Framework/Texture/Texture2D.h"

// �R���X�g���N�^
TitleScene::TitleScene()
{
	Init();
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
	Uninit();
}

// ������
void TitleScene::Init()
{
	// �w�i
	Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/title.png");	//! �摜���w��
	pt->SetPosition(0.0f, 0.0f, 0.0f);					//! �ʒu���w��
	pt->SetRotation(0.0f, 0.0f, 0.0f);					//! �p�x���w��
	pt->SetScale(1920.0f, 1080.0f, 0.0f);				//! �傫�����w��
	m_MySceneObjects.emplace_back(pt);

	// �^�C�g��
	//Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	//pt2->SetTexture("assets/texture/titlerogo.png");		//! �摜���w��
	//pt2->SetPosition(0.0f, 0.0f, 0.0f);					//! �ʒu���w��
	//pt2->SetRotation(0.0f, 0.0f, 0.0f);					//! �p�x���w��
	//pt2->SetScale(1280.0f, 520.0f, 0.0f);				//! �傫�����w��
	//m_MySceneObjects.emplace_back(pt2);
}

// �X�V
void TitleScene::Update()
{
	// �G���^�[�L�[�������ăX�e�[�W1��
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::GetInstance()->ChangeScene(HOLE1);
	}
}

// �I������
void TitleScene::Uninit()
{
	// ���̃V�[���̃I�u�W�F�N�g���폜����
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}
