#include	"TestCube.h"

using namespace DirectX::SimpleMath;

//=======================================
//初期化処理
//=======================================
void TestCube::Init()
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(24);
	
	// 頂点座標設定
	// 上面(1)
	vertices[0].position = Vector3(-10, 10, 10);
	vertices[1].position = Vector3( 10, 10, 10);
	vertices[2].position = Vector3(-10, 10, -10);
	vertices[3].position = Vector3( 10, 10, -10);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);			// 0~1のuv座標を3分割するため1/3
	vertices[1].uv = Vector2(1 / 3.0, 0);	// 1/3だとint型の計算になるのでfloatにする
	vertices[2].uv = Vector2(0, 1 / 2.0);
	vertices[3].uv = Vector2(0.33, 0.5);

	vertices[0].normal = Vector3(0, 1, 0);
	vertices[1].normal = Vector3(0, 1, 0);
	vertices[2].normal = Vector3(0, 1, 0);
	vertices[3].normal = Vector3(0, 1, 0);

	// 手前面(2)
	vertices[4].position = Vector3(-10, 10, -10);
	vertices[5].position = Vector3( 10, 10, -10);
	vertices[6].position = Vector3(-10, -10, -10);
	vertices[7].position = Vector3( 10, -10, -10);

	vertices[4].color = Color(1, 1, 1, 1);
	vertices[5].color = Color(1, 1, 1, 1);
	vertices[6].color = Color(1, 1, 1, 1);
	vertices[7].color = Color(1, 1, 1, 1);
	
	vertices[4].uv = Vector2(0.33, 0);
	vertices[5].uv = Vector2(0.66, 0);
	vertices[6].uv = Vector2(0.33, 0.5);
	vertices[7].uv = Vector2(0.66, 0.5);

	vertices[4].normal = Vector3(0, 0, -1);
	vertices[5].normal = Vector3(0, 0, -1);
	vertices[6].normal = Vector3(0, 0, -1);
	vertices[7].normal = Vector3(0, 0, -1);

	// 下面(6)
	vertices[8].position = Vector3(-10, -10, -10);
	vertices[9].position = Vector3( 10, -10, -10);
	vertices[10].position = Vector3(-10, -10, 10);
	vertices[11].position = Vector3( 10, -10, 10);

	vertices[8].color = Color(1, 1, 1, 1);
	vertices[9].color = Color(1, 1, 1, 1);
	vertices[10].color = Color(1, 1, 1, 1);
	vertices[11].color = Color(1, 1, 1, 1);

	vertices[8].uv = Vector2(0.66, 0.5);
	vertices[9].uv = Vector2(1, 0.5);
	vertices[10].uv = Vector2(0.66, 1);
	vertices[11].uv = Vector2(1, 1);

	vertices[8].normal = Vector3(0, -1, 0);
	vertices[9].normal = Vector3(0, -1, 0);
	vertices[10].normal = Vector3(0, -1, 0);
	vertices[11].normal = Vector3(0, -1, 0);

	// 奥面(5)
	vertices[12].position = Vector3(-10, -10, 10);
	vertices[13].position = Vector3( 10, -10, 10);
	vertices[14].position = Vector3(-10, 10, 10);
	vertices[15].position = Vector3( 10, 10, 10);

	vertices[12].color = Color(1, 1, 1, 1);
	vertices[13].color = Color(1, 1, 1, 1);
	vertices[14].color = Color(1, 1, 1, 1);
	vertices[15].color = Color(1, 1, 1, 1);

	vertices[12].uv = Vector2(0.33, 0.5);
	vertices[13].uv = Vector2(0.66, 0.5);
	vertices[14].uv = Vector2(0.33, 1);
	vertices[15].uv = Vector2(0.66, 1);

	vertices[12].normal = Vector3(0, 0, 1);
	vertices[13].normal = Vector3(0, 0, 1);
	vertices[14].normal = Vector3(0, 0, 1);
	vertices[15].normal = Vector3(0, 0, 1);

	// 右面(3)
	vertices[16].position = Vector3(10, 10, -10);
	vertices[17].position = Vector3(10, 10, 10);
	vertices[18].position = Vector3(10, -10, -10);
	vertices[19].position = Vector3(10, -10, 10);

	vertices[16].color = Color(1, 1, 1, 1);
	vertices[17].color = Color(1, 1, 1, 1);
	vertices[18].color = Color(1, 1, 1, 1);
	vertices[19].color = Color(1, 1, 1, 1);

	vertices[16].uv = Vector2(0.66, 0);
	vertices[17].uv = Vector2(1, 0);
	vertices[18].uv = Vector2(0.66, 0.5);
	vertices[19].uv = Vector2(1, 0.5);

	vertices[16].normal = Vector3(1, 0, 0);
	vertices[17].normal = Vector3(1, 0, 0);
	vertices[18].normal = Vector3(1, 0, 0);
	vertices[19].normal = Vector3(1, 0, 0);

	// 左面(4)
	vertices[20].position = Vector3(-10, 10, 10);
	vertices[21].position = Vector3(-10, 10, -10);
	vertices[22].position = Vector3(-10, -10, 10);
	vertices[23].position = Vector3(-10, -10, -10);

	vertices[20].color = Color(1, 1, 1, 1);
	vertices[21].color = Color(1, 1, 1, 1);
	vertices[22].color = Color(1, 1, 1, 1);
	vertices[23].color = Color(1, 1, 1, 1);

	vertices[20].uv = Vector2(0, 0.5);
	vertices[21].uv = Vector2(0.33, 0.5);
	vertices[22].uv = Vector2(0, 1);
	vertices[23].uv = Vector2(0.33, 1);

	vertices[20].normal = Vector3(-1, 0, 0);
	vertices[21].normal = Vector3(-1, 0, 0);
	vertices[22].normal = Vector3(-1, 0, 0);
	vertices[23].normal = Vector3(-1, 0, 0);

	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);

	// インデックスバッファ（頂点の結び方の順番データ）生成
	std::vector<unsigned int> indices;
	indices.resize(36);

	// 5つの頂点をそれぞれ何番目の頂点とするか
	// 半時計周りにすると裏側表示になりカリング設定で描画されなくなってしまう
	
	indices = {
		// 上面左
		0,1,2,
		// 上面右
		1,3,2,
		// 手前面左
		4,5,6,
		// 手前面右
		5,7,6,
		// 下面左
		8,9,10,
		// 下面右
		9,11,10,
		// 奥面左
		12,13,14,
		// 奥面右
		13,15,14,
		// 右面左
		16,17,18,
		// 右面右
		17,19,18,
		// 左面左
		20,21,22,
		// 左面右
		21,23,22
	};
	

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

	// シェーダオブジェクト生成
	//m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
	m_Shader.Create("Src/Game/Resource/litTextureVS.hlsl", "Src/Game/Resource/litTexturePS.hlsl");

	// テクスチャをロード
	bool sts = m_Texture.Load("assets/texture/dice.png");
	assert(sts == true);
}


//=======================================
//更新処理
//=======================================
void TestCube::Update()
{
	m_Rotation.x += 0.01f;
	m_Rotation.y += 0.01f;
	m_Rotation.z += 0.01f;

}

//=======================================
//描画処理
//=======================================
void TestCube::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll( m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation( m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale( m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// トポロジー（頂点の結び方の規則）をセット（プリミティブタイプ）
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		36,							// 描画するインデックス数（立方体(ポリゴン1面につき3)なので36）
		0,							// 最初のインデックスバッファの位置
		0);
}

//=======================================
//終了処理
//=======================================
void TestCube::Uninit()
{

}