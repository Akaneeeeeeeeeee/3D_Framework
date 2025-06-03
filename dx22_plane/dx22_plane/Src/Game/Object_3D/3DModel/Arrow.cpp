#include <memory>
#include "Arrow.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Utility/utility.h"
#include "../../Game.h"
#include "GolfBall.h"

using namespace std;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
Arrow::Arrow(Camera* cam) :Object(cam)
{

}

// �f�X�g���N�^
Arrow::~Arrow()
{

}

//=======================================
// ����������
//=======================================
void Arrow::Init()
{
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	// 3D���f���f�[�^
	std::u8string modelFile = u8"assets/model/arrow/arrow.fbx";

	// �e�N�X�`���f�B���N�g��
	std::string texDirectory = "assets/model/arrow";

	// Mesh��ǂݍ���
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("Src/Game/Resource/litTextureVS.hlsl", "Src/Game/Resource/litTexturePS.hlsl");

	// �T�u�Z�b�g���擾
	m_subsets = staticmesh.GetSubsets();

	// �e�N�X�`�����擾
	m_Textures = staticmesh.GetTextures();

	// �}�e���A�����擾
	vector<MATERIAL> materials = staticmesh.GetMaterials();

	// �}�e���A���������[�v
	for (int i = 0; i < materials.size(); i++)
	{
		// �}�e���A���I�u�W�F�N�g����
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// �}�e���A�������Z�b�g
		m->Create(materials[i]);

		// �}�e���A���I�u�W�F�N�g��z��ɒǉ�
		m_Materiales.push_back(std::move(m));
	}

	// ���f���ɂ���ăX�P�[���𒲐�
	this->m_Transform.Scale.x = 3;
	this->m_Transform.Scale.y = 3;
	this->m_Transform.Scale.z = 3;

	m_State = 1;
}

//=======================================
// �X�V����(�����I���A�p�x�I���A�����I�����s��)
//=======================================
void Arrow::Update()
{
	if (m_State == 0)return; // ��\���Ȃ�return

	// �S���t�{�[���̈ʒu���擾
	vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
	if (ballpt.size() > 0)
	{
		// ���̈ʒu���X�V
		this->m_Transform.Position = ballpt[0]->GetPosition();
	}

	// �����I���Ȃ�
	if (m_State == 1)
	{
		this->m_Transform.Scale.z = 3; // �������Œ�

		// ��������]������
		this->m_Transform.Rotation.y += 0.03f;

		if (this->m_Transform.Rotation.y > 6.28)this->m_Transform.Rotation.y = 0;
	}
	// �p�x�I���Ȃ�
	else if (m_State == 2)
	{
		//// ��������]
		//m_Rotation.x += 0.01f;

		//// 90�x�ȏ�͉�]���Ȃ�(����܂łŉ�]���Z�b�g)
		//if (m_Rotation.x > 0.78)m_Rotation.y = 0;

		// ���������̌����𒲐�
		static bool up = true;
		if (up)
		{
			this->m_Transform.Rotation.x += 0.01f;
		}
		else
		{
			this->m_Transform.Rotation.x -= 0.01f;
		}

		// �n�ʂ���i0���W�A���ȏ�j�A�����艺�i��/2�����j�ɐ���
		if (this->m_Transform.Rotation.x > 1.57f) {
			this->m_Transform.Rotation.x = 1.57f; // 90�x�����ɐ���
			up = false;
		}
		if (this->m_Transform.Rotation.x < 0.0f) {
			this->m_Transform.Rotation.x = 0.0f;   // �n�ʈȏ�ɐ���
			up = true;
		}
	}
	// �p���[�I���Ȃ�
	else if (m_State == 3)
	{
		// �傫����ύX������
		this->m_Transform.Scale.z += 0.04f;
		if (this->m_Transform.Scale.z > 4)this->m_Transform.Scale.z = 1;
	}
}

//=======================================
// �`�揈��
//=======================================
void Arrow::Draw()
{
	if (m_State == 0) return; // ��\���Ȃ�return

	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll(this->m_Transform.Rotation.y, this->m_Transform.Rotation.x, this->m_Transform.Rotation.z);
	Matrix t = Matrix::CreateTranslation(this->m_Transform.Position.x, this->m_Transform.Position.y, this->m_Transform.Position.z);
	Matrix s = Matrix::CreateScale(this->m_Transform.Scale.x, this->m_Transform.Scale.y, this->m_Transform.Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	m_Shader.SetGPU();

	// �C���f�b�N�X�o�b�t�@�E���_�o�b�t�@���Z�b�g
	m_MeshRenderer.BeforeDraw();

	// �J�����̐ݒ���w��
	m_Camera->SetCamera(0);

	//�}�e���A���������[�v 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		// �}�e���A�����Z�b�g(�T�u�Z�b�g���̒��ɂ���}�e���A���C���f�b�N�X���g�p)
		m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable())
		{
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum, // �`�悷��C���f�b�N�X��
			m_subsets[i].IndexBase, // �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu	
			m_subsets[i].VertexBase); // ���_�o�b�t�@�̍ŏ�����g�p
	}
}

//=======================================
// �I������
//=======================================
void Arrow::Uninit()
{

}


//��Ԃ̐ݒ�
void Arrow::SetState(int s)
{
	m_State = s;
}

// ���̃x�N�g�����擾
Vector3 Arrow::GetVector()
{
	//���̏�����Ԃ̌���
	Vector3 res = { 0, 0, -1 };

	// �x�N�g������]
	Matrix r = Matrix::CreateFromYawPitchRoll(this->m_Transform.Rotation.y, this->m_Transform.Rotation.x, this->m_Transform.Rotation.z);
	res = Vector3::Transform(res, r);

	//���̒���(�p���[)���|����
	res *= this->m_Transform.Scale.z;

	return res;
}


Vector3 Arrow::GetRotation(void)
{
	return this->m_Transform.Rotation;
}


