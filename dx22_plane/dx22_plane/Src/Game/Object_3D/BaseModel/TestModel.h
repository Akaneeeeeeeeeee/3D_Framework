#pragma once
#include <SimpleMath.h>
#include "../../../Framework/Renderer/MeshRenderer.h"
#include "Object.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Utility/utility.h"
#include "../../../Framework/Material/Material.h"

//-----------------------------------------------------------------------------
//TestModel�N���X
//-----------------------------------------------------------------------------
class TestModel :public Object {
private:
	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer; // ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
};
