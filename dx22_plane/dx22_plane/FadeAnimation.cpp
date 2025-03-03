#include "FadeAnimation.h"

using namespace DirectX::SimpleMath;


void FadeAnimation::StartFadeIn(void)
{
	In = true;
	IsPlaying = true;
}

void FadeAnimation::StartFadeOut(void)
{
	In = false;
	IsPlaying = true;
}


bool FadeAnimation::GetIsPlaying(void)
{
	return IsPlaying;
}


void FadeAnimation::Init(void)
{
	m_FrameCount = 0;
	m_Duration = 2.0f;
	m_Alpha = 0.0f;
	m_FPS = 60;
	IsPlaying = false;
	In = false;
}


void FadeAnimation::Update(void)
{
	// �t���[���J�E���g���Z
	m_FrameCount++;


	// �A�j���[�V�����`�撆��
	if (IsPlaying)
	{
		// �t�F�[�h�C���i���]�j���Ȃ�
		if (In)
		{
			FadeIn();
		}
		// �t�F�[�h�A�E�g�i�Ó]�j���Ȃ�
		else
		{
			FadeOut();
		}

		// �t�F�[�h�A�j���[�V�����I������
		if (m_FrameCount >= m_Duration * m_FPS)
		{
			IsPlaying = false; // �A�j���[�V�����I��
			m_FrameCount = 0;  // �J�E���g���Z�b�g
		}
	}
}


void FadeAnimation::FadeIn(void)
{
	m_Alpha += 0.05f; // �����x������������������
	if (m_Alpha > 1.0f)
	{
		m_Alpha = 1.0f;		// �ő哧���x�ɐ���
		In = false;			// �t�F�[�h�C������
		IsPlaying = false;	// �Đ��I��
	}

	// �}�e���A���̐F��ݒ�
	Color col(0.0f, 0.0f, 0.0f, m_Alpha);
	m_Material->SetDiffuse(col);
}


void FadeAnimation::FadeOut(void)
{
	m_Alpha -= 0.05f; // �����x������������������
	if (m_Alpha < 0.0f)
	{
		m_Alpha = 0.0f;		// �ő哧���x�ɐ���
		In = true;			// �t�F�[�h�A�E�g����
		IsPlaying = false;	// �Đ��I��
	}

	// �}�e���A���̐F��ݒ�
	Color col(0.0f, 0.0f, 0.0f, m_Alpha);
	m_Material->SetDiffuse(col);
}
