#pragma once
#include "../../Renderer/IRenderer/IRenderer.h"
#include "../../../Graphics/Graphics.h"
#include "../Shader/Shader.h"

using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

enum class TextureID;

/**
 * @brief 画像描画コンポーネント
 * 
 * 頂点座標
 * 頂点情報
 * インデックスバッファ
 * 画像情報
*/
class SpriteRenderer :public IRenderer
{
public:
	SpriteRenderer() = delete;
	SpriteRenderer(Object* _Owner) :IRenderer(_Owner)
	{

	}
	
	/**
	 * @brief デストラクタ 
	*/
	~SpriteRenderer() {
		// ComPtr(スマートポインタ)なので解放する必要はないが、一応明示的に解放しておく
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();
		m_pTextureView.Reset();
	};

	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Uninit(void) override;

	// 画像と分割数をセットする
	void SetTexture(TextureID _ID ,XMINT2 _split);

	// シェーダーをセット
	void SetShader(std::shared_ptr<Shader> _shader);

private:
	//! 頂点データ
	std::vector<Vertex> m_Vertices;

	// 色
	Color m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// ＜頂点バッファ＞
	// 頂点データ（座標、色、UV座標、法線など）をGPUに送るためのバッファ
	// 頂点ごとの情報を格納し、GPUに渡す。GPUはこのデータを 頂点シェーダー（Vertex Shader）に渡して処理する。
	ComPtr<ID3D11Buffer> m_pVertexBuffer;

	// ＜インデックスバッファ＞
	// 頂点の結ぶ順番（描画する順序）をGPUに送るためのバッファ
	// 頂点バッファに格納された 頂点の順番 を指定する。GPUは インデックスバッファ を使い、頂点を 適切な順番でシェーダーに渡して描画する。
	ComPtr<ID3D11Buffer> m_pIndexBuffer;

	// ＜テクスチャ用変数(画像情報)＞
	/*
	・GPUがテクスチャ（画像）を ピクセルシェーダー（Pixel Shader） で使うときに参照するもの。
	・ただの画像データではなく、「シェーダーがどのように参照するか」を定義する役割もある
	・画像データをシェーダーが扱えるようにするビュー
	・テクスチャ（画像データ）そのものではなく、それにアクセスするためのインターフェース というイメージ
	・画像データ（ID3D11Texture2D）はただのピクセルの集まり → GPUがそのまま使うには情報が足りない
	・スプライト画像一枚ならtexture2D使わなくてもいいけど、別の画像を保持させておきたい場合、texture2dを持たせておくべきってこと？（これは配列かな？わかんないけど。）
	　で、基本的にはtexture2dとsrvはセットで持たせておくっていう認識でOK？
	*/
	// 複数画像を使いたい場合(ミップマップ(解像度ごとに画像を分けて管理)とか)、texture2dも対応付けて持たさないとダメ
	// →今回は画像ファイルから直接SRVを作るのでTexture2Dは使わない
	ComPtr<ID3D11ShaderResourceView> m_pTextureView;

	// DXのリソース管理クラスのID3D11Bufferに渡すための構造体
	ConstBuffer m_ConstantBuffer;


	// ＜シェーダー＞
	std::shared_ptr<Shader> m_pShader;

	// テクスチャが縦横に何分割されているか
	XMINT2 m_Split = { 1,1 };

	// 左上から何段目を切り抜いて表示するか
	XMINT2 m_Number = { 0,0 };
};

