#include "Player.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Input/input.h"
#include <DirectXMath.h>
using namespace DirectX::SimpleMath;


Player::Player(Camera* _cam) :Object(_cam)
{
}

Player::~Player()
{
}

void Player::Init() {
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	//3D���f���f�[�^
	std::u8string modelFile = u8"assets/model/JACK���s�s��_v1.0/JACK���s�s��1.0.pmx";

	//�e�N�X�`���f�B���N�g��
	std::string texDirectory = "assets/model/JACK���s�s��_v1.0";

	//Mesh��ǂݍ���
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
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	// �}�e���A���������[�v
	for (int i = 0; i < materials.size(); i++) {
		// �}�e���A���I�u�W�F�N�g�𐶐�
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// �}�e���A�������Z�b�g
		m->Create(materials[i]);

		// �}�e���A���I�u�W�F�N�g��z��ɒǉ�
		m_Materials.push_back(std::move(m));
	}
}


// 2025/06/04��������
void Player::Update(void)
{
	// �L�[���͂ɂ��ړ�
	/*if (Input::GetKeyPress(VK_W)) {
		Vector3 forward = GetForwardFromYaw(m_Transform.Rotation.y);
		m_Transform.Position += forward * moveSpeed;
	}
	if(Input::GetKeyPress(VK_S)) {
		Vector3 forward = GetForwardFromYaw(m_Transform.Rotation.y);
		m_Transform.Position -= forward * moveSpeed;
	}*/
	
	// �p������E�ړ�
	// �J�����̓L��������������B�L�����͌����Ă�������ɓ����悤�ɂ�����
	float rotateSpeed = 90.0f; // 1�b�ŉ��x��邩�i�x/�b�j
	if (Input::GetKeyPress(VK_A)) {
		m_Transform.Rotation.y -= rotateSpeed;
	}
	if (Input::GetKeyPress(VK_D)) {
		m_Transform.Rotation.y += rotateSpeed;
	}
	
	Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(m_Transform.Rotation.y));
	Matrix world = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(m_Transform.Position);

	Vector3 forward = Vector3::Transform(Vector3(0, 0, 1), rotation);
	if (Input::GetKeyPress(VK_W)) {
		m_Transform.Position += forward * moveSpeed;
	}
	if (Input::GetKeyPress(VK_S)) {
		m_Transform.Position -= forward * moveSpeed;
	}
	
}


void Player::Draw(void)
{
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

	// !�J�����̐ݒ���w��
	m_Camera->SetCamera(0);

	//�}�e���A���������[�v 
	for (int i = 0; i < m_subsets.size(); i++)
	{
		// �}�e���A�����Z�b�g(�T�u�Z�b�g���̒��ɂ���}�e���A���C���f�b�N�X���g�p)
		m_Materials[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materials[m_subsets[i].MaterialIdx]->isTextureEnable())
		{
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum,		// �`�悷��C���f�b�N�X��
			m_subsets[i].IndexBase,		// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu	
			m_subsets[i].VertexBase);	// ���_�o�b�t�@�̍ŏ�����g�p
	}
}



//=======================================
// �I������
//=======================================
void Player::Uninit()
{

}


Vector3 Player::GetForwardFromYaw(float yawDegrees)
{
	float yawRad = DirectX::XMConvertToRadians(yawDegrees);
	return Vector3(
		sinf(yawRad), // X
		0.0f,         // Y�i�n�ʕ��������j
		cosf(yawRad)  // Z
	);
}

// 
void Player::Shot(){

}
