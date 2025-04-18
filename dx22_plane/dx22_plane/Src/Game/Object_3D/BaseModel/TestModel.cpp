#include	<SimpleMath.h>
#include	<memory>
#include	"TestModel.h"
#include	"../../../Framework/Renderer/MeshRenderer.h"
#include	"../../../Framework/Shader/Shader.h"
#include	"../../../Framework/Texture/Texture.h"
#include	"../../../Framework/Mesh/StaticMesh.h"
#include	"../../../Framework/Utility/utility.h"

using namespace DirectX::SimpleMath;

void TestModel::Init()
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ
	std::u8string modelFile = u8"assets/model/JACK式ピピ美_v1.0/JACK式ピピ美1.0.pmx";

	//テクスチャディレクトリ
	std::string texDirectory = "assets/model/JACK式ピピ美_v1.0";

	//Meshを読み込む
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// シェーダオブジェクト生成
	m_Shader.Create("Src/Game/Resource/litTextureVS.hlsl", "Src/Game/Resource/litTexturePS.hlsl");

	// サブセット情報取得
	m_subsets = staticmesh.GetSubsets();

	// テクスチャ情報取得
	m_Textures = staticmesh.GetTextures();

	// マテリアル情報取得
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	// マテリアル数分ループ
	for (int i = 0; i < materials.size(); i++) {
		// マテリアルオブジェクトを生成
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// マテリアル情報をセット
		m->Create(materials[i]);

		// マテリアルオブジェクトを配列に追加
		m_Materials.push_back(std::move(m));
	}
}

void TestModel::Update()
{
	m_Rotation.y += -0.01f;
	m_Scale.x = 5;
	m_Scale.y = 5;
	m_Scale.z = 5;
}

void TestModel::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	m_Shader.SetGPU();

	// インデックスバッファ・頂点バッファをセット
	m_MeshRenderer.BeforeDraw();

	//マテリアル数分ループ 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		// マテリアルをセット（サブセット情報の中にあるマテリアルインデックスを使用）
		m_Materials[m_subsets[i].MaterialIdx]->SetGPU();
		
		if (m_Materials[m_subsets[i].MaterialIdx]->isTextureEnable()) {
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum,    // 描画するインデックス数
			m_subsets[i].IndexBase,   // 最初のインデックスバッファの位置
			m_subsets[i].VertexBase); // 頂点バッファの最初から使用
	}
}

void TestModel::Uninit()
{

}