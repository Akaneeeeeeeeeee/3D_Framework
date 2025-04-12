#include <memory>
#include "Arrow.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Utility/utility.h"
#include "../../Game.h"
#include "GolfBall.h"

using namespace std;
using namespace DirectX::SimpleMath;

// コンストラクタ
Arrow::Arrow(Camera* cam) :Object(cam)
{

}

// デストラクタ
Arrow::~Arrow()
{

}

//=======================================
// 初期化処理
//=======================================
void Arrow::Init()
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	// 3Dモデルデータ
	std::u8string modelFile = u8"assets/model/arrow/arrow.fbx";

	// テクスチャディレクトリ
	std::string texDirectory = "assets/model/arrow";

	// Meshを読み込む
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
	vector<MATERIAL> materials = staticmesh.GetMaterials();

	// マテリアル数分ループ
	for (int i = 0; i < materials.size(); i++)
	{
		// マテリアルオブジェクト生成
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// マテリアル情報をセット
		m->Create(materials[i]);

		// マテリアルオブジェクトを配列に追加
		m_Materiales.push_back(std::move(m));
	}

	// モデルによってスケールを調整
	m_Scale.x = 3;
	m_Scale.y = 3;
	m_Scale.z = 3;

	m_State = 1;
}

//=======================================
// 更新処理(向き選択、角度選択、強さ選択を行う)
//=======================================
void Arrow::Update()
{
	if (m_State == 0)return; // 非表示ならreturn

	// ゴルフボールの位置を取得
	vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
	if (ballpt.size() > 0)
	{
		// 矢印の位置を更新
		m_Position = ballpt[0]->GetPosition();
	}

	// 方向選択なら
	if (m_State == 1)
	{
		m_Scale.z = 3; // 長さを固定

		// 向きを回転させる
		m_Rotation.y += 0.03f;

		if (m_Rotation.y > 6.28)m_Rotation.y = 0;
	}
	// 角度選択なら
	else if (m_State == 2)
	{
		//// 向きを回転
		//m_Rotation.x += 0.01f;

		//// 90度以上は回転しない(直上までで回転リセット)
		//if (m_Rotation.x > 0.78)m_Rotation.y = 0;

		// 垂直方向の向きを調整
		static bool up = true;
		if (up)
		{
			m_Rotation.x += 0.01f;
		}
		else
		{
			m_Rotation.x -= 0.01f;
		}

		// 地面より上（0ラジアン以上）、直上より下（π/2未満）に制限
		if (m_Rotation.x > 1.57f) {
			m_Rotation.x = 1.57f; // 90度未満に制限
			up = false;
		}
		if (m_Rotation.x < 0.0f) {
			m_Rotation.x = 0.0f;   // 地面以上に制限
			up = true;
		}
	}
	// パワー選択なら
	else if (m_State == 3)
	{
		// 大きさを変更させる
		m_Scale.z += 0.04f;
		if (m_Scale.z > 4)m_Scale.z = 1;
	}
}

//=======================================
// 描画処理
//=======================================
void Arrow::Draw()
{
	if (m_State == 0)return; // 非表示ならreturn

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

	// カメラの設定を指定
	m_Camera->SetCamera(0);

	//マテリアル数分ループ 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		// マテリアルをセット(サブセット情報の中にあるマテリアルインデックスを使用)
		m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable())
		{
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum, // 描画するインデックス数
			m_subsets[i].IndexBase, // 最初のインデックスバッファの位置	
			m_subsets[i].VertexBase); // 頂点バッファの最初から使用
	}
}

//=======================================
// 終了処理
//=======================================
void Arrow::Uninit()
{

}


//状態の設定
void Arrow::SetState(int s)
{
	m_State = s;
}

// 矢印のベクトルを取得
Vector3 Arrow::GetVector()
{
	//矢印の初期状態の向き
	Vector3 res = { 0, 0, -1 };

	// ベクトルを回転
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	res = Vector3::Transform(res, r);

	//矢印の長さ(パワー)を掛ける
	res *= m_Scale.z;

	return res;
}


Vector3 Arrow::GetRotation(void)
{
	return m_Rotation;
}

//void Arrow::SetVector(const Vector3& _vec)
//{
//	// ベクトルがゼロかどうかを確認
//	if (_vec.LengthSquared() > 0.0f)
//	{
//		// ベクトルを正規化（方向ベクトルとして使用）
//		Vector3 direction = _vec;
//		direction.Normalize();
//
//		// 方向ベクトルから回転（Quaternion）を計算
//		m_Rotation = Quaternion::CreateFromAxisAngle(Vector3::Cross(defaultForward, direction), acosf(Vector3::Dot(defaultForward, direction)));
//	}
//	else
//	{
//		// ベクトルがゼロの場合は回転をリセット
//		m_Rotation = Quaternion::Identity;
//	}
//}
