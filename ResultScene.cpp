#include "ResultScene.h"
#include "Game.h"
#include "Texture2D.h"

// �R���X�g���N�^
ResultScene::ResultScene()
{
	Init();
}

// �f�X�g���N�^
ResultScene::~ResultScene()
{
	Uninit();
}

// ������
void ResultScene::Init()
{
	// �w�i
	Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/background2.png");	//! �摜���w��
	pt->SetScale(1920.0f, 1080.0f, 0.0f);				//! �傫�����w��
	m_MySceneObjects.emplace_back(pt);

	// ���U���g�����I�u�W�F�N�g
	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/resultString.png");		//! �摜���w��
	pt2->SetPosition(300.0f, 0.0f, 0.0f);					//! �ʒu���w��
	pt2->SetScale(700.0f, 100.0f, 0.0f);					//! �傫�����w��
	pt2->SetUV(1, 1, 1, 13);								//! ��1,�c13�������ꂽ�摜�̍�����1�Ԗ�,�ォ��5�Ԗڂ��w��
	m_MySceneObjects.emplace_back(pt2);

	// �l�I�u�W�F�N�g
	Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	pt3->SetTexture("assets/texture/golf_jou_man.png");		//! �摜���w��
	pt3->SetPosition(-300.0f, 0.0f, 0.0f);					//! �ʒu���w��
	pt3->SetScale(361.0f, 400.0f, 0.0f);					//! �傫�����w��
	m_MySceneObjects.emplace_back(pt3);
}

// �X�V
void ResultScene::Update()
{
	// �G���^�[�L�[�������ă^�C�g����
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::GetInstance()->ChangeScene(TITLE);
	}
}

// �I������
void ResultScene::Uninit()
{
	// ���̃V�[���̃I�u�W�F�N�g���폜����
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

// �X�R�A��ݒ�
void ResultScene::SetScore(int c)
{
	// ���U���g������I�u�W�F�N�g
	Texture2D* stringObj = dynamic_cast<Texture2D*>(m_MySceneObjects[1]);

	switch (c)
	{
	case -4:
		stringObj->SetUV(1, 2, 1, 13);	// -4 �R���h��
		break;
	case -3:
		stringObj->SetUV(1, 3, 1, 13);	// -3 �A���o�g���X
		break;
	case -2:
		stringObj->SetUV(1, 4, 1, 13);	// -2 �C�[�O��
		break;
	case -1:
		stringObj->SetUV(1, 5, 1, 13);	// -1 �o�[�f�B
		break;
	case 0:
		stringObj->SetUV(1, 6, 1, 13);	// 0 �p�[
		break;
	case 1:
		stringObj->SetUV(1, 7, 1, 13);	// +1 �{�M�[
		break;
	case 2:
		stringObj->SetUV(1, 8, 1, 13);	// +2 �_�u���{�M�[
		break;
	case 3:
		stringObj->SetUV(1, 9, 1, 13);	// +3 �g���v���{�M�[
		break;
	case 4:
		stringObj->SetUV(1, 10, 1, 13);	// +4
		break;
	case 5:
		stringObj->SetUV(1, 11, 1, 13);	// +5
		break;
	case 6:
		stringObj->SetUV(1, 12, 1, 13);	// +6
		break;
	default:
		stringObj->SetUV(1, 13, 1, 13);	// +7�ȏ�
		break;
	}
}
