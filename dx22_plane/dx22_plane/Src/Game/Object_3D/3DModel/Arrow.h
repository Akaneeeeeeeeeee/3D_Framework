#pragma once
#include "../BaseModel/Object.h"
#include "../../../Framework/Renderer/MeshRenderer.h"
#include "../../../Framework/Texture/Texture.h"
#include "../../../Framework/Material/Material.h"

using namespace DirectX::SimpleMath;

//-----------------------------------------------------------------------------
// Arrowクラス
//-----------------------------------------------------------------------------
class Arrow :public Object
{
private:

	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer; // 頂点バッファ・インデックスバッファ・インデックス数

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ

	int m_State = 0; // 0:非表示・1:方向選択・2:角度選択・3:パワー選択

public:

	Arrow(Camera* cam); // コンストラクタ
	~Arrow(); // デストラクタ

	void Init();
	void Update();
	void Draw();
	void Uninit();
	
	// 状態の設定
	void SetState(int s);

	// 矢印のベクトルを取得
	Vector3 GetVector();
	void SetVector(const Vector3& _vec);

	Vector3 GetRotation(void);
};

