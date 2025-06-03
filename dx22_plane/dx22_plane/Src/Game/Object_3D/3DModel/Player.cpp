#include "Player.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Input/input.h"

using namespace DirectX::SimpleMath;


Player::Player(Camera* _cam) :Object(_cam)
{
}

Player::~Player()
{
}

void Player::Init(){
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
	this->m_Transform.Scale.x = 2000;
	this->m_Transform.Scale.y = 2000;
	this->m_Transform.Scale.z = 2000;

	this->m_Transform.Position = { 0.0f,0.0f,0.0f };
}



void Player::Update(void)
{
	// キー入力による移動
	if (Input::GetKeyPress(VK_W)) {
		Vector3 forward = GetForwardFromYaw(m_Transform.Rotation.y);
		m_Transform.Position += forward * moveSpeed * deltaTime;
	}
}


void Player::Draw(void)
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll(this->m_Transform.Rotation.y, this->m_Transform.Rotation.x, this->m_Transform.Rotation.z);
	Matrix t = Matrix::CreateTranslation(this->m_Transform.Position.x, this->m_Transform.Position.y, this->m_Transform.Position.z);
	Matrix s = Matrix::CreateScale(this->m_Transform.Scale.x, this->m_Transform.Scale.y, this->m_Transform.Scale.z);

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
void Player::Uninit()
{

}



Vector3 Player::GetForwardFromYaw(float yawDegrees)
{
	float yawRad = DirectX::XMConvertToRadians(yawDegrees);
	return Vector3(
		sinf(yawRad), // X
		0.0f,         // Y（地面方向無視）
		cosf(yawRad)  // Z
	);
}