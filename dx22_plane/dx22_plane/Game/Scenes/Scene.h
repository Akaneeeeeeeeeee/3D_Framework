#pragma once
#include <memory>

//Scene クラス
class Scene
{
public:

	Scene(); // コンストラクタ
	virtual ~Scene(); // デストラクタ(virtualが必要)

	virtual void Update() = 0; // 更新（純粋仮想関数）

protected:
	int m_State = 0;
};
