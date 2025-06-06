#pragma once
#include "../../Game/Object_3D/BaseModel/Object.h"
#include "../Buffer/VertexBuffer.h"
#include "../Buffer/IndexBuffer.h"
#include "Texture.h"
#include "../Material/Material.h"

//-----------------------------------------------------------------------------
// Texture2Dクラス
//-----------------------------------------------------------------------------
class Texture2D : public Object
{
protected:
	// 描画の為の情報（メッシュに関わる情報）
	IndexBuffer m_IndexBuffer; // インデックスバッファ
	VertexBuffer<VERTEX_3D> m_VertexBuffer; // 頂点バッファ

	// 描画の為の情報（見た目に関わる部分）
	Texture m_Texture; // テクスチャ
	std::unique_ptr<Material> m_Material; //マテリアル

	// UV座標の情報
	float m_NumU = 1;
	float m_NumV = 1;
	float m_SplitX = 1;
	float m_SplitY = 1;

public:

	Texture2D(Camera* cam); // コンストラクタ
	virtual ~Texture2D(); // デストラクタ

	void Init();
	void Update();
	void Draw();
	void Uninit();

	// テクスチャを指定
	virtual void SetTexture(const char* imgname);

	// 位置を指定
	void SetPosition(const float& x, const float& y, const float& z);
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);

	// 角度を指定
	void SetRotation(const float& x, const float& y, const float& z);
	void SetRotation(const DirectX::SimpleMath::Vector3& rot);

	// 大きさを指定
	void SetScale(const float& x, const float& y, const float& z);
	void SetScale(const DirectX::SimpleMath::Vector3& scl);

	// 透明度指定
	void SetDiffuse(const float& x, const float& y, const float& z, const float& w);
	void SetDiffuse(const DirectX::SimpleMath::Vector4& dfs);

	// UV座標を指定
	void SetUV(const float& nu, const float& nv, const float& sx, const float& sy);
};

