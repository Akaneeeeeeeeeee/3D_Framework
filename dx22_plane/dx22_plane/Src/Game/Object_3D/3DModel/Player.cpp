#include "Player.h"
#include "../../../Framework/Mesh/StaticMesh.h"
#include "../../../Framework/Input/input.h"

using namespace DirectX::SimpleMath;


Player::Player(Camera* _cam) :Object(_cam)
{
}

Player::~Player()
{
}

void Player::Init(){
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	//3D���f���f�[�^
	// �w�сF�摜�����o����aiStandardSurface�͎g���ȁA�t�H���������o�[�g���g��
	std::u8string modelFile = u8"assets/model/Sphere/SkyDome2.fbx";

	//�e�N�X�`���f�B���N�g��
	std::string texDirectory = "assets/model/Sphere";

	//Mesh��ǂݍ���
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	// �@���t�](�X�J�C�h�[�������̂��ߍ����������ɋL�q)
	staticmesh.InvertNormals();


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
	for (int i = 0; i < materials.size(); i++)
	{
		// �}�e���A���I�u�W�F�N�g����
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// �}�e���A�������Z�b�g
		m->Create(materials[i]);

		// �}�e���A���I�u�W�F�N�g��z��ɒǉ�
		m_Materials.push_back(std::move(m));
	}

	//���f���ɂ���ăX�P�[���𒲐�
	//TODO:(�����F10�ɂ�����X�R�[�v�`���Ă�݂����ɂȂ����I�I�Ȃ񂩂Ɏg���������J�����̃t�@�[�N���b�v�Ƃ��`�揇�ς����瑽�������ƊȒP�ɂł���킱��)
	this->m_Transform.Scale.x = 2000;
	this->m_Transform.Scale.y = 2000;
	this->m_Transform.Scale.z = 2000;

	this->m_Transform.Position = { 0.0f,0.0f,0.0f };
}



void Player::Update(void)
{
	// �L�[���͂ɂ��ړ�
	if (Input::GetKeyPress(VK_W)) {
		Vector3 forward = GetForwardFromYaw(m_Transform.Rotation.y);
		m_Transform.Position += forward * moveSpeed * deltaTime;
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