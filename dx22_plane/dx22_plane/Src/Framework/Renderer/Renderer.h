#pragma once

#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<SimpleMath.h>
#include	<io.h>
#include	<string>
#include	<vector>
#include	<wrl/client.h>

//外部ライブラリ
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

using Microsoft::WRL::ComPtr;

// ３Ｄ頂点データ
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Color color;
	DirectX::SimpleMath::Vector2 uv;
};

// ブレンドステート
enum EBlendState {
	BS_NONE = 0,							// 半透明合成無し	
	BS_ALPHABLEND,							// 半透明合成
	BS_ADDITIVE,							// 加算合成
	BS_SUBTRACTION,							// 減算合成
	MAX_BLENDSTATE
};

// 平行光源
struct LIGHT {
	BOOL Enable;							// 光を使うかのフラグ
	BOOL Dunny[3];							// アラインメント調整用配列
	DirectX::SimpleMath::Vector4 Direction;	// 平行光源の方向
	DirectX::SimpleMath::Color Diffuse;		// 平行光源の強さと色
	DirectX::SimpleMath::Color Ambient;		// 環境光の強さと色
};

// サブセット
struct SUBSET {
	std::string		MtrlName;			// マテリアル名
	unsigned int	IndexNum = 0;		// インデックス数
	unsigned int	VertexNum = 0;		// 頂点数
	unsigned int	IndexBase = 0;		// 開始インデックス数
	unsigned int	VertexBase = 0;		// 頂点ベース
	unsigned int	MaterialIdx = 0;	// マテリアル番号
};

// マテリアル
struct MATERIAL {
	DirectX::SimpleMath::Color Ambient;		// 環境反射
	DirectX::SimpleMath::Color Diffuse;		// 拡散反射
	DirectX::SimpleMath::Color Specular;	// 鏡面反射
	DirectX::SimpleMath::Color Emission;	// 発光
	float Shiness;			// 光沢の滑らかさ
	BOOL TextureEnable;		// テクスチャ使用確認フラグ
	BOOL Dummy[2];			// アラインメント調整

};

//-----------------------------------------------------------------------------
//Rendererクラス
//-----------------------------------------------------------------------------
class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	// 描画系
	static ComPtr<ID3D11Device>				m_Device;
	static ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	static ComPtr<IDXGISwapChain>			m_SwapChain;
	static ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;
	static ComPtr<ID3D11DepthStencilView>	m_DepthStencilView;

	// 行列系
	static ComPtr<ID3D11Buffer> m_WorldBuffer;
	static ComPtr<ID3D11Buffer> m_ViewBuffer;
	static ComPtr<ID3D11Buffer> m_ProjectionBuffer;

	// 光源、質感系
	static ComPtr<ID3D11Buffer>			m_LightBuffer;
	static ComPtr<ID3D11Buffer>			m_MaterialBuffer;
	static ComPtr<ID3D11Buffer>			m_TextureBuffer;	// UV設定

	// 深度バッファ
	static ComPtr<ID3D11DepthStencilState> m_DepthStateEnable;
	static ComPtr<ID3D11DepthStencilState> m_DepthStateDisable;

	// ブレンド ステート
	static ComPtr<ID3D11BlendState>		m_BlendState[MAX_BLENDSTATE];
	static ComPtr<ID3D11BlendState>		m_BlendStateATC;

public:

	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);

	static void SetATCEnable(bool Enable);

	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);
	static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);
	static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);

	static ID3D11Device* GetDevice( void ){ return m_Device.Get(); }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext.Get(); }

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static void SetLight(LIGHT Light);
	static void SetMaterial(MATERIAL Material);
	static void SetUV(float u, float v, float uw, float vh);

	//=============================================================================
	// ブレンド ステート設定
	//=============================================================================
	static void SetBlendState(int nBlendState)
	{
		if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			m_DeviceContext->OMSetBlendState(m_BlendState[nBlendState].Get(), blendFactor, 0xffffffff);
		}
	}
};