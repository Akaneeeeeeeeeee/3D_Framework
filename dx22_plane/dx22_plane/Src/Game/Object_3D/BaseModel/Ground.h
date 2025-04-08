#pragma once
#include "../../../Framework/Texture/Texture.h"
#include "Object.h"
#include "../../../Framework/Material/Material.h"

//-----------------------------------------------------------------------------
//Ground�N���X
//-----------------------------------------------------------------------------
class Ground :public Object {
	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	IndexBuffer	 m_IndexBuffer;				// �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // ���_�o�b�t�@

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	Texture m_Texture;						// �e�N�X�`��
	std::unique_ptr<Material> m_Material;	// �}�e���A��

	// ���̃T�C�Y
	int m_SizeX;		// �c�T�C�Y
	int m_SizeZ;		// ���T�C�Y
	std::vector<VERTEX_3D> m_Vertices;		// ���_���

public:

	Ground(Camera* cam);	//! �R���X�g���N�^
	~Ground();				//! �f�X�g���N�^

	void Init() override;
	void Draw() override;
	void Update() override;
	void Uninit() override;

	void SetImage(const char* _Filepath);

	// ���_�����擾
	std::vector<VERTEX_3D> GetVertices(void);
};

