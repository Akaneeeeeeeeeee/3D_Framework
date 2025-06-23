#include "Player.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Input/input.h"
#include <DirectXMath.h>
using namespace DirectX::SimpleMath;


Player::Player(Camera* _cam) :Object(_cam)
{
}

Player::~Player()
{
}

void Player::Init() {
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


// 2025/06/04ここから
void Player::Update(void)
{
	// キー入力による移動
	/*if (Input::GetKeyPress(VK_W)) {
		Vector3 forward = GetForwardFromYaw(m_Transform.Rotation.y);
		m_Transform.Position += forward * moveSpeed;
	}
	if(Input::GetKeyPress(VK_S)) {
		Vector3 forward = GetForwardFromYaw(m_Transform.Rotation.y);
		m_Transform.Position -= forward * moveSpeed;
	}*/
	
	// 姿勢制御・移動
	// カメラはキャラを見続ける。キャラは向いている方向に動くようにしたい
	float rotateSpeed = 90.0f; // 1秒で何度回るか（度/秒）
	if (Input::GetKeyPress(VK_A)) {
		m_Transform.Rotation.y -= rotateSpeed;
	}
	if (Input::GetKeyPress(VK_D)) {
		m_Transform.Rotation.y += rotateSpeed;
	}
	
	Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(m_Transform.Rotation.y));
	Matrix world = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(m_Transform.Position);

	Vector3 forward = Vector3::Transform(Vector3(0, 0, 1), rotation);
	if (Input::GetKeyPress(VK_W)) {
		m_Transform.Position += forward * moveSpeed;
	}
	if (Input::GetKeyPress(VK_S)) {
		m_Transform.Position -= forward * moveSpeed;
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

// 
void Player::Shot(){

}
