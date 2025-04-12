#include "Game.h"
#include "../Framework/Renderer/Renderer.h"
#include "../Framework/Texture/Texture2D.h"
#include "../Framework/Texture/FadeAnimation.h"
#include "../Framework/ImGui/DebugUI/DebugUI.h"
#include "Scenes/TitleScene.h"
#include "Scenes/Hole1Scene.h"
#include "Scenes/Hole2Scene.h"
#include "Scenes/Hole3Scene.h"
#include "Scenes/ResultScene.h"

Game* Game::m_Instance;

// �R���X�g���N�^
Game::Game()
{
	m_Input = std::make_unique<Input>(); //���͏������쐬
	m_Camera = std::make_unique<Camera>(); //�J�������쐬
}

// �f�X�g���N�^
Game::~Game()
{
	delete m_Scene;
}

// ������
void Game::Init()
{
	// �I�u�W�F�N�g�쐬
	m_Instance = new Game;

	// �`�揉����
	Renderer::Init();
	//! �f�o�b�OUI������
	//DebugUI::Init(Renderer::GetDevice(), Renderer::GetDeviceContext());


	// �I�u�W�F�N�g�z��쐬
	//m_Instance->m_Objects.emplace_back(new GolfBall);
	
	// �J����������
	m_Instance->m_Camera->Init();

	m_Instance->m_Scene = new TitleScene; //���������m��

	/*m_Instance->m_FadeAnimation = std::make_unique<FadeAnimation>(m_Instance->m_Camera.get());
	m_Instance->m_FadeAnimation->SetTexture("assets/texture/ui_back.png");
	m_Instance->m_FadeAnimation->SetPosition(0.0f, 0.0f, 0.0f);
	m_Instance->m_FadeAnimation->SetScale(1920.0f, 1080.0f, 0.0f);*/

			
	// �I�u�W�F�N�g������
	// (��AddObject�֐��Ŏ��s����悤�ɕύX�j
	//for (auto& o : m_Instance->m_Objects)
	//{
	//	o->Init();
	//}
}

// �X�V
// �V�[�����n�܂�Ɠ����Ɏn�܂����V�[�����t�F�[�h�C���A�I������V�[�����t�F�[�h�A�E�g��S������
void Game::Update()
{
	//// �t�F�[�h�A�j���[�V�����̍X�V
	//if (m_Instance->m_FadeAnimation->GetIsPlaying())
	//{
	//	m_Instance->m_FadeAnimation->Update();

	//	// �t�F�[�h�A�E�g������������V�[���ύX
	//	if (!m_Instance->m_FadeAnimation->GetIsPlaying() && m_Instance->Changing)
	//	{
	//		// �V�[���J�ڏ���
	//		if (m_Instance->m_NextSceneName == TITLE)
	//		{
	//			m_Instance->ChangeScene(HOLE1);
	//		}
	//		else if (m_Instance->m_NextSceneName == HOLE2)
	//		{
	//			m_Instance->ChangeScene(HOLE3);
	//		}

	//		m_Instance->m_FadeAnimation->StartFadeIn(); // �t�F�[�h�C���J�n
	//		m_Instance->Changing = false; // �t���O���Z�b�g
	//	}

	//	return; // �t�F�[�h���͑��̍X�V���s��Ȃ�
	//}
	//else
	//{
	//	
	//}
	

	// �V�[���X�V
	m_Instance->m_Scene->Update();

	// �J�����X�V
	m_Instance->m_Camera->Update();

	// ���͏����X�V
	m_Instance->m_Input->Update();

	// �I�u�W�F�N�g�X�V
	for (auto& o : m_Instance->m_Objects)
	{
		o->Update();
	}
	
}



// �`��
void Game::Draw()
{
	// �`��O����
	Renderer::Begin();

	/*DirectX::SimpleMath::Vector4 col;
	if (m_Instance->Changing)
	{
		m_Instance->m_FadeAnimation->Update();
	}
	else
	{
		
	}*/
	
	//! �f�o�b�OUI�̕`��
	//DebugUI::Render();

	// �J�����`��
	m_Instance->m_Camera->Draw();

	// �I�u�W�F�N�g�`��
	for (auto& o : m_Instance->m_Objects)
	{
		o->Draw();
	}

	// �`��㏈��
	Renderer::End();
}

// �I������
void Game::Uninit()
{
	//�I�u�W�F�N�g��S�č폜
	m_Instance->DeleteAllObject();

	// �I�u�W�F�N�g�I������
 	// (��DeleteObject�֐��Ŏ��s����悤�ɕύX�j
	//for (auto& o : m_Instance->m_Objects)
	//{
	//	o->Uninit();
	//}

	// �J�����I������
	m_Instance->m_Camera->Uninit();

	// �`��I������
	Renderer::Uninit();
}

// �C���X�^���X���擾
Game* Game::GetInstance()
{
	return m_Instance;
}

// �J�������擾����
Camera& Game::GetCamera()
{
	return *(m_Instance->m_Camera);
}

// �V�[���؂�ւ��t���O�ݒ�
void Game::SetChange(bool _flg)
{
	Change = _flg;
}

bool Game::GetChange(void)
{
	return Change;
}

void Game::SetChanging(bool _flg)
{
	Changing = _flg;
}

bool Game::GetChanging(void)
{
	return Changing;
}


// �V�[����؂�ւ���
void Game::ChangeScene(SceneName sName)
{
	// �ǂݍ��ݍς݂̃V�[��������΍폜
	static int score = 0;
	if (m_Instance->m_Scene != nullptr)
	{
		int temp = 0;
		// �������Ƃ��Ă���V�[����Stage1�Ȃ�X�R�A��ۑ����Ă���
		if (m_NextSceneName == HOLE2)
		{
			Hole1Scene* sObj = dynamic_cast<Hole1Scene*>(m_Instance->m_Scene);
			temp = sObj->GetTargetScore() - sObj->GetScore();	// �ڕW�X�R�A-���ۂ̃X�R�A�����_

			// �X�R�A��0�𒴂������Ő��I�[�o�[�̏ꍇ
			if (temp > 0)
			{
				temp = sObj->GetScore() - sObj->GetTargetScore();	// �ڕW�X�R�A-���ۂ̃X�R�A�����_
			}

			score += temp;
		}
		else if (m_NextSceneName == HOLE3)
		{
			Hole2Scene* sObj = dynamic_cast<Hole2Scene*>(m_Instance->m_Scene);
			temp = sObj->GetTargetScore() - sObj->GetScore();	// �ڕW�X�R�A-���ۂ̃X�R�A�����_

			// �X�R�A��0�𒴂������Ő��I�[�o�[�̏ꍇ
			if (temp > 0)
			{
				temp = sObj->GetScore() - sObj->GetTargetScore();	// �ڕW�X�R�A-���ۂ̃X�R�A�����_
			}

			score += temp;
		}
		else if (m_NextSceneName == RESULT)
		{
			Hole3Scene* sObj = dynamic_cast<Hole3Scene*>(m_Instance->m_Scene);
			temp = sObj->GetTargetScore() - sObj->GetScore();	// �ڕW�X�R�A-���ۂ̃X�R�A�����_

			// �X�R�A��0�𒴂������Ő��I�[�o�[�̏ꍇ
			if (temp > 0)
			{
				temp = sObj->GetScore() - sObj->GetTargetScore();	// �ڕW�X�R�A-���ۂ̃X�R�A�����_
			}

			score += temp;
		}

		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch (sName)
	{
	case TITLE:
		// �X�R�A�����Z�b�g
		score = 0;
		m_Instance->m_Scene = new TitleScene; // ���������m��
		m_Instance->m_NextSceneName = HOLE1;
		break;
	case HOLE1:
		m_Instance->m_Scene = new Hole1Scene; // ���������m��
		m_Instance->m_NextSceneName = HOLE2;
		break;
	case HOLE2:
		m_Instance->m_Scene = new Hole2Scene; // ���������m��
		m_Instance->m_NextSceneName = HOLE3;
		break;
	case HOLE3:
		m_Instance->m_Scene = new Hole3Scene; // ���������m��
		m_Instance->m_NextSceneName = RESULT;
		break;
	case RESULT:
		m_Instance->m_Scene = new ResultScene; // ���������m��
		dynamic_cast<ResultScene*>(m_Instance->m_Scene)->SetScore(score);	// �X�R�A��ݒ�
		m_Instance->m_NextSceneName = TITLE;
		break;
	}
}

// �I�u�W�F�N�g���폜����
void Game::DeleteObject(Object* pt)
{
	if (pt == NULL) return;

	pt->Uninit(); // �I������

	// �v�f���폜
	m_Instance->m_Objects.erase(
		std::remove_if(
			m_Instance->m_Objects.begin(),
			m_Instance->m_Objects.end(),
			[pt](const std::unique_ptr<Object>& element) {return element.get() == pt; }),
		m_Instance->m_Objects.end());
	m_Instance->m_Objects.shrink_to_fit();
}

// �I�u�W�F�N�g�����ׂč폜����
void Game::DeleteAllObject()
{
	// �I�u�W�F�N�g�I������
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}

	m_Instance->m_Objects.clear(); //�S�č폜
	m_Instance->m_Objects.shrink_to_fit();
}

