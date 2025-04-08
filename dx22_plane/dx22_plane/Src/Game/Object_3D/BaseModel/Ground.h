#pragma once
#include "../../../Framework/Texture/Texture.h"
#include "Object.h"
#include "../../../Framework/Material/Material.h"

//-----------------------------------------------------------------------------
//Groundクラス
//-----------------------------------------------------------------------------
class Ground :public Object {
	// 描画の為の情報（メッシュに関わる情報）
	IndexBuffer	 m_IndexBuffer;				// インデックスバッファ
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // 頂点バッファ

	// 描画の為の情報（見た目に関わる部分）
	Texture m_Texture;						// テクスチャ
	std::unique_ptr<Material> m_Material;	// マテリアル

	// 床のサイズ
	int m_SizeX;		// 縦サイズ
	int m_SizeZ;		// 横サイズ
	std::vector<VERTEX_3D> m_Vertices;		// 頂点情報

public:

	Ground(Camera* cam);	//! コンストラクタ
	~Ground();				//! デストラクタ

	void Init() override;
	void Draw() override;
	void Update() override;
	void Uninit() override;

	void SetImage(const char* _Filepath);

	// 頂点情報を取得
	std::vector<VERTEX_3D> GetVertices(void);
};

