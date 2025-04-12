#pragma once
#include "../BaseModel/Object.h"
#include "../../../Framework/Renderer/MeshRenderer.h"
#include "../../../Framework/Texture/Texture.h"
#include "../../../Framework/Material/Material.h"

using namespace DirectX::SimpleMath;

//-----------------------------------------------------------------------------
// Arrow�N���X
//-----------------------------------------------------------------------------
class Arrow :public Object
{
private:

	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer; // ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

	int m_State = 0; // 0:��\���E1:�����I���E2:�p�x�I���E3:�p���[�I��

public:

	Arrow(Camera* cam); // �R���X�g���N�^
	~Arrow(); // �f�X�g���N�^

	void Init();
	void Update();
	void Draw();
	void Uninit();
	
	// ��Ԃ̐ݒ�
	void SetState(int s);

	// ���̃x�N�g�����擾
	Vector3 GetVector();
	void SetVector(const Vector3& _vec);

	Vector3 GetRotation(void);
};

