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
	float m_Duration;	// アニメーション秒数
	float m_Alpha;		// 透明度設定用変数
	int m_FrameCount;	// フレーム数カウント変数
	int m_FPS;			// フレームレート
	bool IsPlaying;		// アニメーション中かの判定
	bool In;			// フェードイン・アウトの判定 true:フェードイン,false:フェードアウト
};


