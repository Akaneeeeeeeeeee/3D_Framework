#include "Hole2Scene.h"
#include "Game.h"
#include "GolfBall.h"
#include "Ground.h"
#include "Texture2D.h"
#include "Arrow.h"
#include "Pole.h"
#include "Sphere.h"

using namespace DirectX::SimpleMath;

// �R���X�g���N�^
Hole2Scene::Hole2Scene()
{
	Init();
}

// �f�X�g���N�^
Hole2Scene::~Hole2Scene()
{
	Uninit();
}

// ������
void Hole2Scene::Init()
{

	m_Par = 4;			// �p�[�i�W���Ő��j��ݒ�
	m_StrokeCount = 0;	// ���ݑŐ���������

	// �I�u�W�F�N�g���쐬
	Ground* ground = Game::GetInstance()->AddObject<Ground>();
	ground->SetImage("assets/texture/Hole2.jpg");	// �n�`��ݒ�
	m_MySceneObjects.emplace_back(ground);					// �n��


	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<GolfBall>());	// �S���t�{�[��
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Arrow>());		// ���
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Pole>());		// �|�[��

	// UI�i�w�i�j
	Texture2D* pt1 = Game::GetInstance()->AddObject<Texture2D>();
	pt1->SetTexture("assets/texture/ui_back.png");		// �摜���w��
	pt1->SetPosition(-475.0f, -300.0f, 0.0f);			// �ʒu���w��
	pt1->SetScale(270.0f, 75.0f, 0.0f);					// �傫�����w��
	m_MySceneObjects.emplace_back(pt1);

	// UI�i�p�[�j
	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/ui_string.png");	// �摜���w��
	pt2->SetPosition(-575.0f, -245.0f, 0.0f);			// �ʒu���w��
	pt2->SetScale(60.0f, 45.0f, 0.0f);					// �傫�����w��
	pt2->SetUV(1, 1, 2, 1);								// UV���w��
	m_MySceneObjects.emplace_back(pt2);

	// UI�i�Ŗځj
	Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	pt3->SetTexture("assets/texture/ui_string.png");	// �摜���w��
	pt3->SetPosition(-400.0f, -305.0f, 0.0f);			// �ʒu���w��
	pt3->SetScale(105.0f, 63.0f, 0.0f);					// �傫�����w��
	pt3->SetUV(2, 1, 2, 1);								// UV���w��
	m_MySceneObjects.emplace_back(pt3);

	// UI�i�p�[�̐��l�j
	Texture2D* pt4 = Game::GetInstance()->AddObject<Texture2D>();
	pt4->SetTexture("assets/texture/number.png");		// �摜���w��
	pt4->SetPosition(-510.0f, -245.0f, 0.0f);			// �ʒu���w��
	pt4->SetScale(65.0f, 45.0f, 0.0f);					// �傫�����w��
	pt4->SetUV(m_Par + 1, 1, 10, 1);					// UV���w��
	m_MySceneObjects.emplace_back(pt4);

	// UI�i���ݑŐ��F��̈ʁj
	Texture2D* pt5 = Game::GetInstance()->AddObject<Texture2D>();
	pt5->SetTexture("assets/texture/number.png");		// �摜���w��
	pt5->SetPosition(-490.0f, -300.0f, 0.0f);			// �ʒu���w��
	pt5->SetScale(95.0f, 72.0f, 0.0f);					// �傫�����w��
	pt5->SetUV(2, 1, 10, 1);							// UV���w��
	m_MySceneObjects.emplace_back(pt5);

	// UI�i���ݑŐ��F�\�̈ʁj
	Texture2D* pt6 = Game::GetInstance()->AddObject<Texture2D>();
	pt6->SetTexture("assets/texture/number.png");		// �摜���w��
	pt6->SetPosition(-565.0f, -300.0f, 0.0f);			// �ʒu���w��
	pt6->SetScale(95.0f, 72.0f, 0.0f);					// �傫�����w��
	pt6->SetUV(1, 1, 10, 1);							// UV���w��
	m_MySceneObjects.emplace_back(pt6);

	// UI�i�w�i�j
	Texture2D* pt7 = Game::GetInstance()->AddObject<Texture2D>();
	pt7->SetTexture("assets/texture/ui_back.png");		// �摜���w��
	pt7->SetPosition(-735.0f, 490.0f, 0.0f);			// �ʒu���w��
	pt7->SetScale(430.0f, 100.0f, 0.0f);					// �傫�����w��
	m_MySceneObjects.emplace_back(pt7);

	// ��Z�z�[��
	Texture2D* pt8 = Game::GetInstance()->AddObject<Texture2D>();
	pt8->SetTexture("assets/texture/HoleNumber.png");	// �摜���w��
	pt8->SetPosition(-735.0f, 490.0f, 0.0f);			// �ʒu���w��
	pt8->SetScale(430.0f, 100.0f, 0.0f);					// �傫�����w��
	pt8->SetUV(1, 1, 1, 1);								// UV���w��
	m_MySceneObjects.emplace_back(pt8);

	// �z�[����
	Texture2D* pt9 = Game::GetInstance()->AddObject<Texture2D>();
	pt9->SetTexture("assets/texture/number.png");	// �摜���w��
	pt9->SetPosition(-815.0f, 495.0f, 0.0f);			// �ʒu���w��
	pt9->SetScale(50.0f, 100.0f, 0.0f);					// �傫�����w��
	pt9->SetUV(3, 1, 10, 1);							// UV���w��
	m_MySceneObjects.emplace_back(pt9);

	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Sphere>());	// �X�J�C�h�[��



	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[1]);		// �S���t�{�[��
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);			// ���
	Pole* pole = dynamic_cast<Pole*>(m_MySceneObjects[3]);				// �|�[��

	ball->SetState(0);		// �{�[���𕨗�����������
	arrow->SetState(0);		// �����\��
	pole->SetPosition(20.0f, 0.0f, -40.0f);		// �|�[���̏ꏊ��ݒ�


}

//�X�V
void Hole2Scene::Update()
{
	//// �V�[���J�ڏ������ł͂Ȃ��ꍇ�A�V�[���̍X�V
	//if (!Game::GetInstance()->GetChange() && !Game::GetInstance()->GetChanging())
	//{
	//	
	//}
	//// �V�[���J�ڏ������̏ꍇ
	//else if (Game::GetInstance()->GetChanging()&& Game::GetInstance()->GetChange())
	//{
	//	//Game::GetInstance()->
	//}
	//else
	//{
	//	// �t�F�[�h�A�E�g����
	//}


	GolfBall* ball = dynamic_cast<GolfBall*>(m_MySceneObjects[1]);	// �S���t�{�[��
	Arrow* arrow = dynamic_cast<Arrow*>(m_MySceneObjects[2]);		// ���

	// ��Ԃ��Ƃɏ���
	switch (m_State)
	{
		// �{�[���ړ���
	case 0:
		// �{�[�����Î~������
		if (ball->GetState() == 1)
		{
			m_State = 1;
			arrow->SetState(m_State);

			// �Ő����X�V
			Texture2D* count[2];
			count[0] = dynamic_cast<Texture2D*>(m_MySceneObjects[8]);
			count[1] = dynamic_cast<Texture2D*>(m_MySceneObjects[9]);

			m_StrokeCount++;	// ���ݑŐ����J�E���g�A�b�v

			// �e������납��擾���Ă���
			for (int i = 0; i < 2; i++)
			{
				// �ꌅ���o��
				int cnt = m_StrokeCount % (int)pow(10, i + 1) / (int)pow(10, i);

				// UV��ݒ�
				count[i]->SetUV(cnt + 1, 1, 10, 1);
			}
		}
		// �{�[�����J�b�v�C�������烊�U���g��
		if (ball->GetState() == 2)
		{
			Game::GetInstance()->ChangeScene(HOLE3);
		}
		break;
		// �����I��
	case 1:
		// �X�y�[�X�L�[�Ńp���[�I����
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			m_State = 2;
			arrow->SetState(m_State);
		}
		break;
		// �p�x�I��
	case 2:
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			m_State = 3;
			//ball->SetState(m_State);
			arrow->SetState(m_State);


		}
		break;
		// �p���[�I��
	case 3:
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			m_State = 0;
			ball->SetState(m_State);
			arrow->SetState(m_State);

			// ������ݒ�
			Vector3 v = arrow->GetVector();
			v *= 1.25f;
			ball->Shot(v);
		}
		break;
	default:
		break;
	}

	// �G���^�[�L�[�������ă^�C�g����
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::GetInstance()->ChangeScene(HOLE3);
	}

}

// �I������
void Hole2Scene::Uninit()
{
	// ���̃V�[���̃I�u�W�F�N�g���폜����
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

// �X�R�A���擾
int Hole2Scene::GetScore(void)
{
	// ���ݑŐ�����W���Ő����������l��Ԃ�
	return (m_StrokeCount - m_Par);
}

int Hole2Scene::GetTargetScore(void)
{
	return m_Par;
}
