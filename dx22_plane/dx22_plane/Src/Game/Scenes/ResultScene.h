#pragma once
#include "Scene.h"
#include "../Object_3D/BaseModel/Object.h"

// ResultSceneクラス
class ResultScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

	void Init();			// 初期化
	void Uninit();			// 終了処理

public:
	ResultScene();			// コンストラクタ
	~ResultScene();			// デストラクタ

	void Update();			// 更新

	void SetScore(int c);	// スコアを設定
};

