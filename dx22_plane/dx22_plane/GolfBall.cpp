#include <memory>
#include "GolfBall.h"
#include "StaticMesh.h"
#include "utility.h"
#include "Collision.h"
#include "input.h"
#include "Game.h"
#include "Ground.h"
#include "Pole.h"

using namespace std;
using namespace DirectX::SimpleMath;

/**
 * @brief コンストラクタ
 * @param cam 基底クラスであるオブジェクトクラスのカメラを初期化するためのカメラ型ポインタ
*/
GolfBall::GolfBall(Camera* cam) :Object(cam) {

}

/**
 * @brief デストラクタ
*/
GolfBall::~GolfBall() {

}

void GolfBall::Init()
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ
	std::u8string modelFile = u8"assets/model/golfball2/golf_ball.obj";

	//テクスチャディレクトリ
	std::string texDirectory = "assets/model/golfball2";

	//Meshを読み込む
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// シェーダオブジェクト生成
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

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
	m_Scale.x = 1;
	m_Scale.y = 1;
	m_Scale.z = 1;

	// 最初に速度を与える(最初の1フレームあたりどれくらいの速度か)
	//m_Velocity.x = 0.5f;
	m_Position = { 0.0f,0.0f,0.0f };
}

void GolfBall::Update()
{
	if (m_State != 0) return;		// 静止状態ならreturn

	Vector3 oldPos = m_Position;	// 1フレーム前の位置を記憶しておく

	// 速度が0に近づいたら停止
	if (m_Velocity.LengthSquared() < 0.03f) {
		m_StopConut++;
		//m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	}
	else {
		m_StopConut = 0;
		// 減速度(1フレームあたりどれくらい減速するか)
		float decelerationPower = 0.05f;		// 元値0.005f
		Vector3 deceleration = -m_Velocity;		// 速度の逆ベクトルを計算
		deceleration.Normalize();				// ベクトルを正規化
		m_Acceleration = deceleration * decelerationPower;

		// 加速度を速度に加算(逆方向に進もうとする)
		m_Velocity += m_Acceleration;
	}

	// 10フレーム連続でほとんど動いていなければ静止状態へ
	if (m_StopConut > 10) {
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_State = 1;		// 静止状態
	}

	// 重力
	const float gravity = 0.098f;		// 重力は9.8f
	m_Velocity.y -= gravity;

	// 速度を座標に加算
	m_Position += m_Velocity;

	float radius = 2.0f;

	// Groundの頂点データを取得;
	//std::vector<VERTEX_3D> vertices = m_Ground->GetVertices();
	vector<Ground*> grounds = Game::GetInstance()->GetObjects<Ground>();
	vector<VERTEX_3D> vertices;
	for (auto g: grounds )
	{
		vector<VERTEX_3D> vecs = g->GetVertices();
		for (auto& v : vecs)
		{
			vertices.emplace_back(v);
		}
	}

	float moveDistance = 9999;		// 移動距離
	Vector3 contactPoint;			// 接触点
	Vector3 normal;

	// 球体の線分とポリゴンの当たり判定
	bool line_segment = false;
	for (int i = 0; i < vertices.size(); i += 3)
	{
		// 3角形ポリゴン
		Collision::Polygon collisionPolygon = {
			vertices[i + 0].position,
			vertices[i + 1].position,
			vertices[i + 2].position
		};

		Vector3 cp;			// 接触点
		Collision::Segment collisionSegment = { oldPos,m_Position };
		if (Collision::CheckHit(collisionSegment, collisionPolygon, cp))
		{
			float md = 0;
			Vector3 np = Collision::moveSphere(collisionSegment,radius, collisionPolygon, cp, md);
			if (moveDistance > md)
			{
				moveDistance = md;
				m_Position = np;
				contactPoint = cp;
				normal = Collision::GetNormal(collisionPolygon);
			}
			line_segment = true;
		}
	}

	// 球体とポリゴンの当たり判定
	if (!line_segment) {
		for (int i = 0; i < vertices.size(); i += 3)
		{
			// 3角形ポリゴン
			Collision::Polygon collisionPolygon = {
				vertices[i + 0].position,
				vertices[i + 1].position,
				vertices[i + 2].position
			};

			Vector3 cp;			// 接触点
			Collision::Sphere collisionSphere = { m_Position,radius };
			if (Collision::CheckHit(collisionSphere, collisionPolygon, cp))
			{
				float md = 0;
				Vector3 np = Collision::moveSphere(collisionSphere, collisionPolygon, cp);
				md = (np - oldPos).Length();
				if (moveDistance > md)
				{
					moveDistance = md;
					m_Position = np;
					contactPoint = cp;
					normal = Collision::GetNormal(collisionPolygon);
				}
			}
		}
	}

	// もし当たっていたら
	if (moveDistance != 9999)
	{
		m_Velocity.y = -gravity;

		//! ボールの速度ベクトルの法線方向成分と接線方向成分を分解
		float velocityNormal = Collision::Dot(m_Velocity, normal);
		Vector3 v1 = velocityNormal * normal;		//! 法線方向成分
		Vector3 v2 = m_Velocity - v1;				//! 接線方向成分

		//! 反発係数
		const float restitution = 0.05f;
		
		//! 反射ベクトルを計算
		Vector3 reflectedVelocity = v2 - restitution * v1;

		//! ボールの速度を更新
		m_Velocity = reflectedVelocity;
	}

	// 下に落ちた時はリスポーン
	if (m_Position.y < -100)
	{
		m_Position = Vector3(0.0f, 50.0f, 0.0f);
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	}

	// ポールの位置を取得
	vector<Pole*> pole = Game::GetInstance()->GetObjects<Pole>();
	if (pole.size() > 0) {
		Vector3 polePos = pole[0]->GetPosition();
		Collision::Sphere ballCollision = { m_Position,radius };	// ゴルフボールの当たり判定
		Collision::Sphere poleCollision = { polePos,0.5f };			// ポールの当たり判定
		if (Collision::CheckHit(ballCollision, poleCollision))
		{
			m_State = 2;	// カップイン
		}
	}
}

void GolfBall::Draw()
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

/**
 * @brief 終了処理
*/
void GolfBall::Uninit()
{

}

// 状態の設定・取得
void GolfBall::SetState(int s) { m_State = s; }
int GolfBall::GetState(void) { return m_State; }

// ショット
void GolfBall::Shot(Vector3 v) { m_Velocity = v; }		// ボール移動中, 1:方向選択中, 2:パワー選択中
