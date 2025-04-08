#include "SpriteRenderer.h"
#include "../../../ResourceManager/ResourceManager.h"
#include "../../../../Game/Objcet/BaseObject/Object.h"


void SpriteRenderer::Init(void)
{
	// 頂点情報初期化
	m_Vertices = {
		//   x     y    z       r    g    b    a     u    v
		{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },	// 0番目の頂点座標
		{ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },	// 1番目の頂点座標
		{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },	// 2番目の頂点座標
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },	// 3番目の頂点座標
	};


	// 頂点バッファを作成する
	// ※頂点バッファ→VRAMに頂点データを置くための機能
	D3D11_BUFFER_DESC bufferDesc;
	//bufferDesc.ByteWidth = sizeof(vertices);	// 確保するバッファサイズを指定（vectorなので注意）
	bufferDesc.ByteWidth = static_cast<UINT>(m_Vertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = m_Vertices.data();	// VRAMに送るデータを指定（vectorなので注意）
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = Graphics::GetInstance().GetDevice()->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
}

/**
 * @brief 更新処理
 * ここで描画まで行ってしまう
*/
void SpriteRenderer::Update(void)
{
	//頂点バッファを設定
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	Graphics::GetInstance().GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	// テクスチャをピクセルシェーダーに渡す
	Graphics::GetInstance().GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTextureView);


	// 定数バッファを更新
	// プロジェクション変換行列を作成
	m_ConstantBuffer.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	m_ConstantBuffer.matrixProj = DirectX::XMMatrixTranspose(m_ConstantBuffer.matrixProj);

	// ワールド変換行列の作成
	// →オブジェクトの位置・大きさ・向きを指定
	TransformComponent* transform = m_pOwner->GetComponent<TransformComponent>();
	m_ConstantBuffer.matrixWorld = DirectX::XMMatrixScaling(transform->GetScale().x, transform->GetScale().y, transform->GetScale().z);
	m_ConstantBuffer.matrixWorld *= DirectX::XMMatrixRotationZ(transform->GetRotation().z * 3.14f / 180);
	m_ConstantBuffer.matrixWorld *= DirectX::XMMatrixTranslation(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);
	m_ConstantBuffer.matrixWorld = DirectX::XMMatrixTranspose(m_ConstantBuffer.matrixWorld);

	// UVアニメーションの行列作成
	float u = static_cast<float>(m_Number.x) / m_Split.x;
	float v = static_cast<float>(m_Number.y) / m_Split.y;
	m_ConstantBuffer.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	m_ConstantBuffer.matrixTex = DirectX::XMMatrixTranspose(m_ConstantBuffer.matrixTex);

	//頂点カラーのデータを作成
	m_ConstantBuffer.color = m_Color;	
}


void SpriteRenderer::Render(void)
{
	// 行列をシェーダーに渡す
	Graphics::GetInstance().GetDeviceContext()->UpdateSubresource(Graphics::GetInstance().GetConstantBuffer(), 0, NULL, &m_ConstantBuffer, 0, 0);
	// 描画命令
	Graphics::GetInstance().GetDeviceContext()->Draw(4, 0);

}


void SpriteRenderer::Uninit(void)
{
	m_pShader.reset();
}


/**
 * @brief テクスチャ設定
 * @param _ID 登録されているID
 * @param _split 画像分割数
*/
void SpriteRenderer::SetTexture(TextureID _ID, XMINT2 _split)
{
	// リソースマネージャに登録されているIDからSRVを取得して登録
	this->m_pTextureView = ResourceManager::GetInstance().GetSRV(_ID);
	// 分割数設定
	this->m_Split = _split;
	m_Vertices[1].u = 1.0f / m_Split.x;
	m_Vertices[2].v = 1.0f / m_Split.y;
	m_Vertices[3].u = 1.0f / m_Split.x;
	m_Vertices[3].v = 1.0f / m_Split.y;
}

/**
 * @brief シェーダー設定
 * @param _shader リソースマネージャから持ってきたシェーダーのshared_ptr
*/
void SpriteRenderer::SetShader(std::shared_ptr<Shader> _shader)
{
	this->m_pShader = _shader;
}
