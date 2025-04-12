#include "Ground.h"
#include "../../../Framework/stb_image/stb_image.h"
#include <iostream>

using namespace DirectX::SimpleMath;

/**
 * @brief コンストラクタ
 * @param cam カメラのポインタ
*/
Ground::Ground(Camera* cam) :Object(cam) {

}

/**
 * @brief デストラクタ
*/
Ground::~Ground() {

}


//=======================================
//初期化処理
//=======================================
void Ground::Init()
{
	// 頂点データ
	//std::vector<VERTEX_3D>	m_Vertices;

	m_SizeX = 30;
	m_SizeZ = 30;

	m_Vertices.resize(6 * m_SizeX * m_SizeZ);

	//// 頂点座標設定（Z）
	//m_Vertices[0].position = Vector3(-10, 0, 10);
	//m_Vertices[1].position = Vector3(10, 0, 10);
	//m_Vertices[2].position = Vector3(-10, 0, -10);
	//m_Vertices[3].position = Vector3(10, 0, -10);

	//m_Vertices[0].color = Color(1, 1, 1, 1);
	//m_Vertices[1].color = Color(1, 1, 1, 1);
	//m_Vertices[2].color = Color(1, 1, 1, 1);
	//m_Vertices[3].color = Color(1, 1, 1, 1);

	//m_Vertices[0].uv = Vector2(0, 0);
	//m_Vertices[1].uv = Vector2(1, 0);
	//m_Vertices[2].uv = Vector2(0, 1);
	//m_Vertices[3].uv = Vector2(1, 1);

	//m_Vertices[0].normal = Vector3(0, 1, 0);
	//m_Vertices[1].normal = Vector3(0, 1, 0);
	//m_Vertices[2].normal = Vector3(0, 1, 0);
	//m_Vertices[3].normal = Vector3(0, 1, 0);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(6 * m_SizeX * m_SizeZ);

	for (int z = 0; z < m_SizeZ; z++) {
		for (int x = 0; x < m_SizeX; x++) {
			
			int n = z * m_SizeZ * 6 + x * 6;
			m_Vertices[n + 0].position = Vector3(-0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 1].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 2].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 3].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 4].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 5].position = Vector3(0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);

			m_Vertices[n + 0].color = Color(1, 1, 1, 1);
			m_Vertices[n + 1].color = Color(1, 1, 1, 1);
			m_Vertices[n + 2].color = Color(1, 1, 1, 1);
			m_Vertices[n + 3].color = Color(1, 1, 1, 1);
			m_Vertices[n + 4].color = Color(1, 1, 1, 1);
			m_Vertices[n + 5].color = Color(1, 1, 1, 1);

			m_Vertices[n + 0].uv = Vector2(0, 0);
			m_Vertices[n + 1].uv = Vector2(1, 0);
			m_Vertices[n + 2].uv = Vector2(0, 1);
			m_Vertices[n + 3].uv = Vector2(0, 1);
			m_Vertices[n + 4].uv = Vector2(1, 0);
			m_Vertices[n + 5].uv = Vector2(1, 1);

			m_Vertices[n + 0].normal = Vector3(0, 1, 0);
			m_Vertices[n + 1].normal = Vector3(0, 1, 0);
			m_Vertices[n + 2].normal = Vector3(0, 1, 0);
			m_Vertices[n + 3].normal = Vector3(0, 1, 0);
			m_Vertices[n + 4].normal = Vector3(0, 1, 0);
			m_Vertices[n + 5].normal = Vector3(0, 1, 0);

			indices[n + 0] = n + 0;
			indices[n + 1] = n + 1;
			indices[n + 2] = n + 2;
			indices[n + 3] = n + 3;
			indices[n + 4] = n + 4;
			indices[n + 5] = n + 5;
		}
	}

	// 読み込む画像のファイルパス
	//const char* filename = _Filepath;
	/*const char* filename = "assets/texture/20180831135320.jpg";

	SetImage(filename);*/
	//// 画像データを格納するポインタ
	//unsigned char* imageData = nullptr;
	//int width, height, channels;

	//// グレースケール（１チャネル）で画像を読み込む
	//imageData = stbi_load(filename, &width, &height, &channels, 1);
	//if (imageData) {
	//	for (int z = 0; z < m_SizeZ; z++) {
	//		for (int x = 0; x < m_SizeX; x++) {

	//			int picX = x * (float)width / m_SizeX;
	//			int picY = z * (float)height / m_SizeZ;
	//			unsigned char pixelValue = imageData[picY * width + picX];
	//			float h = (float)pixelValue / 15.0f;	// Y座標
	//			int n = z * m_SizeZ * 6 + x * 6;
	//			m_Vertices[n + 0].position.y = h;			// 0番目の頂点のy座標をいじる
	//			// 左隣の四角の頂点
	//			if (x != 0)m_Vertices[n - 2].position.y = h;
	//			if (x != 0)m_Vertices[n - 5].position.y = h;

	//			if (z != 0)m_Vertices[n - m_SizeX * 6 + 2].position.y = h;
	//			if (z != 0)m_Vertices[n - m_SizeX * 6 + 3].position.y = h;

	//			if (x != 0 && z != 0)m_Vertices[n - m_SizeX * 6 - 1].position.y = h;
	//			// if分の{}の省略は、初めて出てくる";"までが処理としてカウントされる
	//		}
	//	}

	//	// 頂点ごとの法線を保持する配列
	//	std::vector<Vector3> vertexNormals(m_Vertices.size(), Vector3(0.0f, 0.0f, 0.0f));

	//	// 四角形ごとの法線ベクトルを更新
	//	for (int z = 0; z < m_SizeZ; z++) {
	//		for (int x = 0; x < m_SizeX; x++) {
	//			// 四角形を構成する頂点データは一次元配列で連続して管理されている
	//			// 配列内のどの頂点（インデックス）から計算するかを求める
	//			int n = z * m_SizeZ * 6 + x * 6;

	//			// 0番目の頂点から他の2つ頂点へのベクトルを計算(2辺分で十分→三角形の面の定義は頂点１つとその頂点を通る２つのベクトルであるため)
	//			Vector3 v1 = m_Vertices[n + 1].position - m_Vertices[n + 0].position;
	//			Vector3 v2 = m_Vertices[n + 2].position - m_Vertices[n + 0].position;
	//			Vector3 normal = v1.Cross(v2);		// 外積で法線を計算
	//			normal.Normalize();					// 正規化
	//			m_Vertices[n + 0].normal = normal;
	//			m_Vertices[n + 1].normal = normal;
	//			m_Vertices[n + 2].normal = normal;

	//			// 各頂点に法線を加算
	//			vertexNormals[n + 0] += normal;
	//			vertexNormals[n + 1] += normal;
	//			vertexNormals[n + 2] += normal;

	//			// 2つのベクトルを計算
	//			v1 = m_Vertices[n + 4].position - m_Vertices[n + 3].position;
	//			v2 = m_Vertices[n + 5].position - m_Vertices[n + 3].position;
	//			normal = v1.Cross(v2);				// 外積で法線を計算
	//			normal.Normalize();					// 正規化
	//			m_Vertices[n + 3].normal = normal;
	//			m_Vertices[n + 4].normal = normal;
	//			m_Vertices[n + 5].normal = normal;

	//			// 各頂点に法線を加算
	//			vertexNormals[n + 3] += normal;
	//			vertexNormals[n + 4] += normal;
	//			vertexNormals[n + 5] += normal;
	//		}
	//	}

	//	// バラバラの向きを向いている法線の向きの平均を取って各頂点に代入
	//	// →地面の１つの頂点の法線の向きが統一され、シェーディングが綺麗になる
	//	// 頂点法線を正規化して設定
	//	for (size_t i = 0; i < m_Vertices.size(); i++) {
	//		vertexNormals[i].Normalize();		// 法線を正規化
	//		m_Vertices[i].normal = vertexNormals[i];

	//	}

	//	// メモリを解放
	//	stbi_image_free(imageData);
	//}
		
	// 頂点バッファ生成
	m_VertexBuffer.Create(m_Vertices);
	
	//// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

	// シェーダオブジェクト生成
	//m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
	m_Shader.Create("Src/Game/Resource/litTextureVS.hlsl", "Src/Game/Resource/litTexturePS.hlsl");

	// テクスチャをロード
	bool sts = m_Texture.Load("assets/texture/field.jpg");
	assert(sts == true);

	// マテリアル情報取得
	m_Material = std::make_unique<Material>();
	MATERIAL mtrl;
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Shiness = 1;
	mtrl.TextureEnable = true;		// テクスチャ使用確認フラグ
	m_Material->Create(mtrl);


	// ワールド座標への変換は凹凸情報を設定してから行う！！

	//// Groundの位置や大きさを調整
	/*m_Position.y = -20.0f;
	m_Scale.x = 20.0f;
	m_Scale.z = 20.0f;*/

	//// 頂点情報を変換
	//Matrix r = Matrix::CreateFromYawPitchRoll(
	//	m_Rotation.y,
	//	m_Rotation.x,
	//	m_Rotation.z);

	//Matrix t = Matrix::CreateTranslation(
	//	m_Position.x,
	//	m_Position.y,
	//	m_Position.z);

	//Matrix s = Matrix::CreateScale(
	//	m_Scale.x,
	//	m_Scale.y,
	//	m_Scale.z);

	//Matrix worldmtx = s * r * t;	// WorldMatrix：世界の中の自分の情報を持った行列
	//// 頂点数分ループ
	//for (int i = 0; i < m_Vertices.size(); i++) {
	//	m_Vertices[i].position = Vector3::Transform(m_Vertices[i].position, worldmtx);
	//	m_Vertices[i].normal = Vector3::Transform(m_Vertices[i].normal, worldmtx);
	//}
}


//=======================================
//更新処理
//=======================================
void Ground::Update()
{
	/*m_Position.y = -20;
	m_Scale.x = 3;
	m_Scale.z = 3;*/

}

//=======================================
//描画処理
//=======================================
void Ground::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll(
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	Matrix worldmtx;		// WorldMatrix：世界の中の自分の情報を持った行列
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// トポロジーをセット（プリミティブタイプ）
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();

	m_Material->SetGPU();

	//! カメラ設定を指定
	m_Camera->SetCamera(0);

	devicecontext->DrawIndexed(
		6 * m_SizeX * m_SizeZ,		// 描画するインデックス数（四角形なので４）
		0,							// 最初のインデックスバッファの位置
		0);
}

//=======================================
//終了処理
//=======================================
void Ground::Uninit()
{

}

void Ground::SetImage(const char* _Filepath)
{
	// 読み込む画像のファイルパス
	const char* filename = _Filepath;

	// 画像データを格納するポインタ
	unsigned char* imageData = nullptr;
	int width, height, channels;

	// グレースケール（１チャネル）で画像を読み込む
	imageData = stbi_load(filename, &width, &height, &channels, 1);
	if (imageData) {
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {

				int picX = x * (float)width / m_SizeX;
				int picY = z * (float)height / m_SizeZ;
				unsigned char pixelValue = imageData[picY * width + picX];
				float h = (float)pixelValue / 15.0f;	// Y座標
				int n = z * m_SizeZ * 6 + x * 6;
				m_Vertices[n + 0].position.y = h;			// 0番目の頂点のy座標をいじる
				// 左隣の四角の頂点
				if (x != 0)m_Vertices[n - 2].position.y = h;
				if (x != 0)m_Vertices[n - 5].position.y = h;

				if (z != 0)m_Vertices[n - m_SizeX * 6 + 2].position.y = h;
				if (z != 0)m_Vertices[n - m_SizeX * 6 + 3].position.y = h;

				if (x != 0 && z != 0)m_Vertices[n - m_SizeX * 6 - 1].position.y = h;
				// if分の{}の省略は、初めて出てくる";"までが処理としてカウントされる
			}
		}

		// 頂点ごとの法線を保持する配列
		std::vector<Vector3> vertexNormals(m_Vertices.size(), Vector3(0.0f, 0.0f, 0.0f));

		// 四角形ごとの法線ベクトルを更新
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {
				// 四角形を構成する頂点データは一次元配列で連続して管理されている
				// 配列内のどの頂点（インデックス）から計算するかを求める
				int n = z * m_SizeZ * 6 + x * 6;

				// 0番目の頂点から他の2つ頂点へのベクトルを計算(2辺分で十分→三角形の面の定義は頂点１つとその頂点を通る２つのベクトルであるため)
				Vector3 v1 = m_Vertices[n + 1].position - m_Vertices[n + 0].position;
				Vector3 v2 = m_Vertices[n + 2].position - m_Vertices[n + 0].position;
				Vector3 normal = v1.Cross(v2);		// 外積で法線を計算
				normal.Normalize();					// 正規化
				m_Vertices[n + 0].normal = normal;
				m_Vertices[n + 1].normal = normal;
				m_Vertices[n + 2].normal = normal;

				// 各頂点に法線を加算
				vertexNormals[n + 0] += normal;
				vertexNormals[n + 1] += normal;
				vertexNormals[n + 2] += normal;

				// 2つのベクトルを計算
				v1 = m_Vertices[n + 4].position - m_Vertices[n + 3].position;
				v2 = m_Vertices[n + 5].position - m_Vertices[n + 3].position;
				normal = v1.Cross(v2);				// 外積で法線を計算
				normal.Normalize();					// 正規化
				m_Vertices[n + 3].normal = normal;
				m_Vertices[n + 4].normal = normal;
				m_Vertices[n + 5].normal = normal;

				// 各頂点に法線を加算
				vertexNormals[n + 3] += normal;
				vertexNormals[n + 4] += normal;
				vertexNormals[n + 5] += normal;
			}
		}

		// バラバラの向きを向いている法線の向きの平均を取って各頂点に代入
		// →地面の１つの頂点の法線の向きが統一され、シェーディングが綺麗になる
		// 頂点法線を正規化して設定
		for (size_t i = 0; i < m_Vertices.size(); i++) {
			vertexNormals[i].Normalize();		// 法線を正規化
			m_Vertices[i].normal = vertexNormals[i];

		}

		// メモリを解放
		stbi_image_free(imageData);
	}

	// 頂点バッファ書き換え
	m_VertexBuffer.Modify(m_Vertices);


	// Groundの位置や大きさを調整
	m_Position.y = -20.0f;
	m_Scale.x = 20.0f;
	m_Scale.z = 20.0f;

	// 頂点情報を変換
	Matrix r = Matrix::CreateFromYawPitchRoll(
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	Matrix worldmtx;		// WorldMatrix：世界の中の自分の情報を持った行列
	worldmtx = s * r * t;

	// 頂点数分ループ
	for (int i = 0; i < m_Vertices.size(); i++) {
		m_Vertices[i].position = Vector3::Transform(m_Vertices[i].position, worldmtx);
		m_Vertices[i].normal = Vector3::Transform(m_Vertices[i].normal, worldmtx);
	}
}

//=======================================
// 頂点情報を取得
//=======================================
std::vector<VERTEX_3D> Ground::GetVertices(void)
{
	return m_Vertices;
}