#include "Sphere.h"
#include "../../../Framework/Mesh/StaticMesh.h"

using namespace DirectX::SimpleMath;

void Sphere::Init(void)
{
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
	m_Scale.x = 2000;
	m_Scale.y = 2000;
	m_Scale.z = 2000;

	m_Position = { 0.0f,0.0f,0.0f };
}


void Sphere::Update(void)
{

}


void Sphere::Draw(void)
{
	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);

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
void Sphere::Uninit()
{

}


//void Sphere::Generate(int segments, float radius) {
//
//	// �ܓx�ilatitude�j�ƌo�x�ilongitude�j�̊p�x���v�Z
//	for (int lat = 0; lat <= segments; ++lat) {
//		float theta = lat * M_PI / segments;  // �ܓx�p
//		float sinTheta = sin(theta);
//		float cosTheta = cos(theta);
//
//		for (int lon = 0; lon <= segments; ++lon) {
//			float phi = lon * 2 * M_PI / segments;  // �o�x�p
//			float sinPhi = sin(phi);
//			float cosPhi = cos(phi);
//
//			// ���̏�̓_�̍��W���v�Z
//			float x = radius * cosTheta * cosPhi;
//			float y = radius * sinTheta;
//			float z = radius * cosTheta * sinPhi;
//
//			// �@���x�N�g���i���_�ʒu�ƈ�v�j
//			float nx = x / radius;
//			float ny = y / radius;
//			float nz = z / radius;
//
//			// UV���W���v�Z
//			float u = (float)lon / segments;
//			float v = (float)lat / segments;
//
//			// ���_�f�[�^��ǉ�
//			m_Vertices.push_back(
//				{ DirectX::SimpleMath::Vector3(x, y, z),  // �ʒu
//				DirectX::SimpleMath::Vector3(nx, ny, nz),  // �@��
//				DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),  // �F�i���j
//				DirectX::SimpleMath::Vector2(u, v)  // UV���W
//				}
//			);
//		}
//	}
//
//	// �C���f�b�N�X�f�[�^�𐶐��i���̖̂ʂ��O�p�`�Ƃ��Č��ԁj
//	for (int lat = 0; lat < segments; ++lat) {
//		for (int lon = 0; lon < segments; ++lon) {
//			int first = (lat * (segments + 1)) + lon;
//			int second = first + segments + 1;
//
//			// 2�̎O�p�`���쐬
//			m_Indices.push_back(first);
//			m_Indices.push_back(second);
//			m_Indices.push_back(first + 1);
//
//			m_Indices.push_back(second);
//			m_Indices.push_back(second + 1);
//			m_Indices.push_back(first + 1);
//		}
//	}
//
//	
//}
