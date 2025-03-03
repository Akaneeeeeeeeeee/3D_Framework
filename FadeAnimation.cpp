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
	// フレームカウント加算
	m_FrameCount++;


	// アニメーション描画中で
	if (IsPlaying)
	{
		// フェードイン（明転）中なら
		if (In)
		{
			FadeIn();
		}
		// フェードアウト（暗転）中なら
		else
		{
			FadeOut();
		}

		// フェードアニメーション終了判定
		if (m_FrameCount >= m_Duration * m_FPS)
		{
			IsPlaying = false; // アニメーション終了
			m_FrameCount = 0;  // カウントリセット
		}
	}
}


void FadeAnimation::FadeIn(void)
{
	m_Alpha += 0.05f; // 透明度を少しずつ増加させる
	if (m_Alpha > 1.0f)
	{
		m_Alpha = 1.0f;		// 最大透明度に制限
		In = false;			// フェードイン完了
		IsPlaying = false;	// 再生終了
	}

	// マテリアルの色を設定
	Color col(0.0f, 0.0f, 0.0f, m_Alpha);
	m_Material->SetDiffuse(col);
}


void FadeAnimation::FadeOut(void)
{
	m_Alpha -= 0.05f; // 透明度を少しずつ増加させる
	if (m_Alpha < 0.0f)
	{
		m_Alpha = 0.0f;		// 最大透明度に制限
		In = true;			// フェードアウト完了
		IsPlaying = false;	// 再生終了
	}

	// マテリアルの色を設定
	Color col(0.0f, 0.0f, 0.0f, m_Alpha);
	m_Material->SetDiffuse(col);
}
