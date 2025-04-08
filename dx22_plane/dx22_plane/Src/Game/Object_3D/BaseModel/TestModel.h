#pragma once
#include <SimpleMath.h>
#include "../../../Framework/Renderer/MeshRenderer.h"
#include "Object.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Utility/utility.h"
#include "../../../Framework/Material/Material.h"

//-----------------------------------------------------------------------------
//TestModelクラス
//-----------------------------------------------------------------------------
class TestModel :public Object {
private:
	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer; // 頂点バッファ・インデックスバッファ・インデックス数

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
};
