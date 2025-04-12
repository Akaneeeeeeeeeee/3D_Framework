#include "Sphere.h"
#include "../../../Framework/Mesh/StaticMesh.h"

using namespace DirectX::SimpleMath;

void Sphere::Init(void)
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ
	// 学び：画像書き出しでaiStandardSurfaceは使うな、フォンかランバートを使え
	std::u8string modelFile = u8"assets/model/Sphere/SkyDome2.fbx";

	//テクスチャディレクトリ
	std::string texDirectory = "assets/model/Sphere";

	//Meshを読み込む
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	// 法線逆転(スカイドーム実装のため今だけここに記述)
	staticmesh.InvertNormals();


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
	for (int i = 0; i < materials.size(); i++)
	{
		// マテリアルオブジェクト生成
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// マテリアル情報をセット
		m->Create(materials[i]);

		// マテリアルオブジェクトを配列に追加
		m_Materials.push_back(std::move(m));
	}

	//モデルによってスケールを調整
	//TODO:(メモ：10にしたらスコープ覗いてるみたいになった！！なんかに使えそう→カメラのファークリップとか描画順変えたら多分もっと簡単にできるわこれ)
	m_Scale.x = 2000;
	m_Scale.y = 2000;
	m_Scale.z = 2000;

	m_Position = { 0.0f,0.0f,0.0f };
}


void Sphere::Update(void)
{

}


void Sphere::Draw(void)
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

	// !カメラの設定を指定
	m_Camera->SetCamera(0);

	//マテリアル数分ループ 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		// マテリアルをセット(サブセット情報の中にあるマテリアルインデックスを使用)
		m_Materials[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materials[m_subsets[i].MaterialIdx]->isTextureEnable())
		{
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum,		// 描画するインデックス数
			m_subsets[i].IndexBase,		// 最初のインデックスバッファの位置	
			m_subsets[i].VertexBase);	// 頂点バッファの最初から使用
	}
}


//=======================================
// 終了処理
//=======================================
void Sphere::Uninit()
{

}


//void Sphere::Generate(int segments, float radius) {
//
//	// 緯度（latitude）と経度（longitude）の角度を計算
//	for (int lat = 0; lat <= segments; ++lat) {
//		float theta = lat * M_PI / segments;  // 緯度角
//		float sinTheta = sin(theta);
//		float cosTheta = cos(theta);
//
//		for (int lon = 0; lon <= segments; ++lon) {
//			float phi = lon * 2 * M_PI / segments;  // 経度角
//			float sinPhi = sin(phi);
//			float cosPhi = cos(phi);
//
//			// 球体上の点の座標を計算
//			float x = radius * cosTheta * cosPhi;
//			float y = radius * sinTheta;
//			float z = radius * cosTheta * sinPhi;
//
//			// 法線ベクトル（頂点位置と一致）
//			float nx = x / radius;
//			float ny = y / radius;
//			float nz = z / radius;
//
//			// UV座標を計算
//			float u = (float)lon / segments;
//			float v = (float)lat / segments;
//
//			// 頂点データを追加
//			m_Vertices.push_back(
//				{ DirectX::SimpleMath::Vector3(x, y, z),  // 位置
//				DirectX::SimpleMath::Vector3(nx, ny, nz),  // 法線
//				DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),  // 色（白）
//				DirectX::SimpleMath::Vector2(u, v)  // UV座標
//				}
//			);
//		}
//	}
//
//	// インデックスデータを生成（球体の面を三角形として結ぶ）
//	for (int lat = 0; lat < segments; ++lat) {
//		for (int lon = 0; lon < segments; ++lon) {
//			int first = (lat * (segments + 1)) + lon;
//			int second = first + segments + 1;
//
//			// 2つの三角形を作成
//			m_Indices.push_back(first);
//			m_Indices.push_back(second);
//			m_Indices.push_back(first + 1);
//
//			m_Indices.push_back(second);
//			m_Indices.push_back(second + 1);
//			m_Indices.push_back(first + 1);
//		}
//	}
//
//	
//}
