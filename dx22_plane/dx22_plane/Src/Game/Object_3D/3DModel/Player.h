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
	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer;	// ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��]

	float moveSpeed = 1.0f;			// �ړ����x

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��
};

