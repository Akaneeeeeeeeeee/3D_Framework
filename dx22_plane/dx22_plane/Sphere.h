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
	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer;			// ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

};

