#include	"TestPlane.h"

using namespace DirectX::SimpleMath;

//=======================================
//初期化処理
//=======================================
void TestPlane::Init()
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	// 頂点座標設定（Z）
	vertices[0].position = Vector3(-10,  0,  10);
	vertices[1].position = Vector3( 10,  0,  10);
	vertices[2].position = Vector3(-10,  0, -10);
	vertices[3].position = Vector3( 10,  0, -10);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(0, 1);
	vertices[3].uv = Vector2(1, 1);

	vertices[0].normal = Vector3(0, 1, 0);
	vertices[1].normal = Vector3(0, 1, 0);
	vertices[2].normal = Vector3(0, 1, 0);
	vertices[3].normal = Vector3(0, 1, 0);

	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

	// シェーダオブジェクト生成
	m_Shader.Create("Src/Game/Resource/unlitTextureVS.hlsl","Src/Game/Resource/unlitTexturePS.hlsl");
	//m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	// テクスチャをロード
	bool sts = m_Texture.Load("assets/texture/field.jpg");
	assert(sts == true);
}


//=======================================
//更新処理
//=======================================
void TestPlane::Update()
{
	m_Position.y = -20;
	m_Scale.x = 3;
	m_Scale.z = 3;

}

//=======================================
//描画処理
//=======================================
void TestPlane::Draw()
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
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		4,							// 描画するインデックス数（四角形なので４）
		0,							// 最初のインデックスバッファの位置
		0);
}

//=======================================
//終了処理
//=======================================
void TestPlane::Uninit()
{

}