#pragma once
#include "Scene.h"
#include "Object.h"


// 1ホール目
class Hole2Scene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

	void Init();		// 初期化
	void Uninit();		// 終了処理

	int m_Par;			// パー（標準打数）
	int m_StrokeCount;	// 現在の打数

public:
	Hole2Scene();			// コンストラクタ
	~Hole2Scene();			// デストラクタ

	void Update();			// 更新

	int GetTargetScore(void);
	int GetScore(void);	// スコアを取得
};

