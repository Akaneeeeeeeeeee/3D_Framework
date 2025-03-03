#pragma once
#include "Texture.h"
#include "Object.h"

//-----------------------------------------------------------------------------
//TestCube�N���X
//-----------------------------------------------------------------------------
class TestCube :public Object {
	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	IndexBuffer	 m_IndexBuffer; // �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // ���_�o�b�t�@

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	Texture m_Texture;	// �e�N�X�`��

public:
	void Init();
	void Draw();
	void Update();
	void Uninit();
};