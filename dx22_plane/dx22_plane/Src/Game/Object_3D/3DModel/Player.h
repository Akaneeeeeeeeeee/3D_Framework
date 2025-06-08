#pragma once
#include "../BaseModel/Object.h"
#include "../../../Framework/Renderer/MeshRenderer.h"
#include "../../../Framework/Texture/Texture.h"
#include "../../../Framework/Material/Material.h"

class Player : public Object
{
public:
	Player(Camera* _cam);
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	void Shot();
	Vector3 GetForwardFromYaw(float yawDegrees);
private:
	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer;	// 頂点バッファ・インデックスバッファ・インデックス数]

	float moveSpeed = 1.0f;			// 移動速度

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ
};

