#pragma once
#include "Texture2D.h"

class FadeAnimation : public Texture2D
{
public:

	FadeAnimation(Camera* _cam) :Texture2D(_cam) {
		m_Duration = 0.0f;
		m_FrameCount = 0;
		m_FPS = 0;
		m_Alpha = 0.0f;
		IsPlaying = false;
		In = false;
	}

	~FadeAnimation() {};

	void Init(void);
	void Update(void);

	void StartFadeIn(void);
	void StartFadeOut(void);
	void FadeIn(void);
	void FadeOut(void);

	bool GetIsPlaying(void);

private:
	float m_Duration;	// �A�j���[�V�����b��
	float m_Alpha;		// �����x�ݒ�p�ϐ�
	int m_FrameCount;	// �t���[�����J�E���g�ϐ�
	int m_FPS;			// �t���[�����[�g
	bool IsPlaying;		// �A�j���[�V���������̔���
	bool In;			// �t�F�[�h�C���E�A�E�g�̔��� true:�t�F�[�h�C��,false:�t�F�[�h�A�E�g
};


