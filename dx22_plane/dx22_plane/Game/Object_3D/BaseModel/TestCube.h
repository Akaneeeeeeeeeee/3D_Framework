#pragma once
#include "Texture.h"
#include "Object.h"

//-----------------------------------------------------------------------------
//TestCubeクラス
//-----------------------------------------------------------------------------
class TestCube :public Object {
	// 描画の為の情報（メッシュに関わる情報）
	IndexBuffer	 m_IndexBuffer; // インデックスバッファ
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // 頂点バッファ

	// 描画の為の情報（見た目に関わる部分）
	Texture m_Texture;	// テクスチャ

public:
	void Init();
	void Draw();
	void Update();
	void Uninit();
};