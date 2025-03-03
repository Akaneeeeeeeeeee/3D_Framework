#pragma once
#include "Object.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"

class GolfBall :public Object
{
private:
	// ���x
	DirectX::SimpleMath::Vector3 m_Velocity{ 0.0f,0.0f,0.0f };

	// �����x
	DirectX::SimpleMath::Vector3 m_Acceleration{ 0.0f,0.0f,0.0f };

	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer; // ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

	int m_State = 0;		// ���	0:��������, 1:��~, 2:�J�b�v�C��
	int m_StopConut = 0;	// �Î~�J�E���g

public:
	
	GolfBall(Camera* cam);	//! �R���X�g���N�^
	~GolfBall();			//! �f�X�g���N�^

	void Init();
	void Update();
	void Draw();
	void Uninit();

	// ��Ԃ̐ݒ�E�擾
	void SetState(int s);
	int GetState();

	// �V���b�g
	void Shot(DirectX::SimpleMath::Vector3 v);

};

