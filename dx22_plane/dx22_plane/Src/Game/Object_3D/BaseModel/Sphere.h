#pragma once

#include "Object.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"
#include <math.h>

#define M_PI 3.14159265358979323846


class Sphere : public Object
{
public:
	Sphere(Camera* _cam) :Object(_cam) {

	};

	~Sphere() {};

	void Init();
	void Update();
	void Draw();
	void Uninit();

	//void Generate(int segments, float radius);


private:
	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer;			// 頂点バッファ・インデックスバッファ・インデックス数

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ

};

