#include "Ground.h"
#include "../../../Framework/stb_image/stb_image.h"
#include <iostream>

using namespace DirectX::SimpleMath;

/**
 * @brief �R���X�g���N�^
 * @param cam �J�����̃|�C���^
*/
Ground::Ground(Camera* cam) :Object(cam) {

}

/**
 * @brief �f�X�g���N�^
*/
Ground::~Ground() {

}


//=======================================
//����������
//=======================================
void Ground::Init()
{
	// ���_�f�[�^
	//std::vector<VERTEX_3D>	m_Vertices;

	m_SizeX = 30;
	m_SizeZ = 30;

	m_Vertices.resize(6 * m_SizeX * m_SizeZ);

	//// ���_���W�ݒ�iZ�j
	//m_Vertices[0].position = Vector3(-10, 0, 10);
	//m_Vertices[1].position = Vector3(10, 0, 10);
	//m_Vertices[2].position = Vector3(-10, 0, -10);
	//m_Vertices[3].position = Vector3(10, 0, -10);

	//m_Vertices[0].color = Color(1, 1, 1, 1);
	//m_Vertices[1].color = Color(1, 1, 1, 1);
	//m_Vertices[2].color = Color(1, 1, 1, 1);
	//m_Vertices[3].color = Color(1, 1, 1, 1);

	//m_Vertices[0].uv = Vector2(0, 0);
	//m_Vertices[1].uv = Vector2(1, 0);
	//m_Vertices[2].uv = Vector2(0, 1);
	//m_Vertices[3].uv = Vector2(1, 1);

	//m_Vertices[0].normal = Vector3(0, 1, 0);
	//m_Vertices[1].normal = Vector3(0, 1, 0);
	//m_Vertices[2].normal = Vector3(0, 1, 0);
	//m_Vertices[3].normal = Vector3(0, 1, 0);

	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(6 * m_SizeX * m_SizeZ);

	for (int z = 0; z < m_SizeZ; z++) {
		for (int x = 0; x < m_SizeX; x++) {
			
			int n = z * m_SizeZ * 6 + x * 6;
			m_Vertices[n + 0].position = Vector3(-0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 1].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 2].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 3].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 4].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 5].position = Vector3(0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);

			m_Vertices[n + 0].color = Color(1, 1, 1, 1);
			m_Vertices[n + 1].color = Color(1, 1, 1, 1);
			m_Vertices[n + 2].color = Color(1, 1, 1, 1);
			m_Vertices[n + 3].color = Color(1, 1, 1, 1);
			m_Vertices[n + 4].color = Color(1, 1, 1, 1);
			m_Vertices[n + 5].color = Color(1, 1, 1, 1);

			m_Vertices[n + 0].uv = Vector2(0, 0);
			m_Vertices[n + 1].uv = Vector2(1, 0);
			m_Vertices[n + 2].uv = Vector2(0, 1);
			m_Vertices[n + 3].uv = Vector2(0, 1);
			m_Vertices[n + 4].uv = Vector2(1, 0);
			m_Vertices[n + 5].uv = Vector2(1, 1);

			m_Vertices[n + 0].normal = Vector3(0, 1, 0);
			m_Vertices[n + 1].normal = Vector3(0, 1, 0);
			m_Vertices[n + 2].normal = Vector3(0, 1, 0);
			m_Vertices[n + 3].normal = Vector3(0, 1, 0);
			m_Vertices[n + 4].normal = Vector3(0, 1, 0);
			m_Vertices[n + 5].normal = Vector3(0, 1, 0);

			indices[n + 0] = n + 0;
			indices[n + 1] = n + 1;
			indices[n + 2] = n + 2;
			indices[n + 3] = n + 3;
			indices[n + 4] = n + 4;
			indices[n + 5] = n + 5;
		}
	}

	// �ǂݍ��މ摜�̃t�@�C���p�X
	//const char* filename = _Filepath;
	/*const char* filename = "assets/texture/20180831135320.jpg";

	SetImage(filename);*/
	//// �摜�f�[�^���i�[����|�C���^
	//unsigned char* imageData = nullptr;
	//int width, height, channels;

	//// �O���[�X�P�[���i�P�`���l���j�ŉ摜��ǂݍ���
	//imageData = stbi_load(filename, &width, &height, &channels, 1);
	//if (imageData) {
	//	for (int z = 0; z < m_SizeZ; z++) {
	//		for (int x = 0; x < m_SizeX; x++) {

	//			int picX = x * (float)width / m_SizeX;
	//			int picY = z * (float)height / m_SizeZ;
	//			unsigned char pixelValue = imageData[picY * width + picX];
	//			float h = (float)pixelValue / 15.0f;	// Y���W
	//			int n = z * m_SizeZ * 6 + x * 6;
	//			m_Vertices[n + 0].position.y = h;			// 0�Ԗڂ̒��_��y���W��������
	//			// ���ׂ̎l�p�̒��_
	//			if (x != 0)m_Vertices[n - 2].position.y = h;
	//			if (x != 0)m_Vertices[n - 5].position.y = h;

	//			if (z != 0)m_Vertices[n - m_SizeX * 6 + 2].position.y = h;
	//			if (z != 0)m_Vertices[n - m_SizeX * 6 + 3].position.y = h;

	//			if (x != 0 && z != 0)m_Vertices[n - m_SizeX * 6 - 1].position.y = h;
	//			// if����{}�̏ȗ��́A���߂ďo�Ă���";"�܂ł������Ƃ��ăJ�E���g�����
	//		}
	//	}

	//	// ���_���Ƃ̖@����ێ�����z��
	//	std::vector<Vector3> vertexNormals(m_Vertices.size(), Vector3(0.0f, 0.0f, 0.0f));

	//	// �l�p�`���Ƃ̖@���x�N�g�����X�V
	//	for (int z = 0; z < m_SizeZ; z++) {
	//		for (int x = 0; x < m_SizeX; x++) {
	//			// �l�p�`���\�����钸�_�f�[�^�͈ꎟ���z��ŘA�����ĊǗ�����Ă���
	//			// �z����̂ǂ̒��_�i�C���f�b�N�X�j����v�Z���邩�����߂�
	//			int n = z * m_SizeZ * 6 + x * 6;

	//			// 0�Ԗڂ̒��_���瑼��2���_�ւ̃x�N�g�����v�Z(2�ӕ��ŏ\�����O�p�`�̖ʂ̒�`�͒��_�P�Ƃ��̒��_��ʂ�Q�̃x�N�g���ł��邽��)
	//			Vector3 v1 = m_Vertices[n + 1].position - m_Vertices[n + 0].position;
	//			Vector3 v2 = m_Vertices[n + 2].position - m_Vertices[n + 0].position;
	//			Vector3 normal = v1.Cross(v2);		// �O�ςŖ@�����v�Z
	//			normal.Normalize();					// ���K��
	//			m_Vertices[n + 0].normal = normal;
	//			m_Vertices[n + 1].normal = normal;
	//			m_Vertices[n + 2].normal = normal;

	//			// �e���_�ɖ@�������Z
	//			vertexNormals[n + 0] += normal;
	//			vertexNormals[n + 1] += normal;
	//			vertexNormals[n + 2] += normal;

	//			// 2�̃x�N�g�����v�Z
	//			v1 = m_Vertices[n + 4].position - m_Vertices[n + 3].position;
	//			v2 = m_Vertices[n + 5].position - m_Vertices[n + 3].position;
	//			normal = v1.Cross(v2);				// �O�ςŖ@�����v�Z
	//			normal.Normalize();					// ���K��
	//			m_Vertices[n + 3].normal = normal;
	//			m_Vertices[n + 4].normal = normal;
	//			m_Vertices[n + 5].normal = normal;

	//			// �e���_�ɖ@�������Z
	//			vertexNormals[n + 3] += normal;
	//			vertexNormals[n + 4] += normal;
	//			vertexNormals[n + 5] += normal;
	//		}
	//	}

	//	// �o���o���̌����������Ă���@���̌����̕��ς�����Ċe���_�ɑ��
	//	// ���n�ʂ̂P�̒��_�̖@���̌��������ꂳ��A�V�F�[�f�B���O���Y��ɂȂ�
	//	// ���_�@���𐳋K�����Đݒ�
	//	for (size_t i = 0; i < m_Vertices.size(); i++) {
	//		vertexNormals[i].Normalize();		// �@���𐳋K��
	//		m_Vertices[i].normal = vertexNormals[i];

	//	}

	//	// �����������
	//	stbi_image_free(imageData);
	//}
		
	// ���_�o�b�t�@����
	m_VertexBuffer.Create(m_Vertices);
	
	//// �C���f�b�N�X�o�b�t�@����
	m_IndexBuffer.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	//m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
	m_Shader.Create("Src/Game/Resource/litTextureVS.hlsl", "Src/Game/Resource/litTexturePS.hlsl");

	// �e�N�X�`�������[�h
	bool sts = m_Texture.Load("assets/texture/field.jpg");
	assert(sts == true);

	// �}�e���A�����擾
	m_Material = std::make_unique<Material>();
	MATERIAL mtrl;
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Shiness = 1;
	mtrl.TextureEnable = true;		// �e�N�X�`���g�p�m�F�t���O
	m_Material->Create(mtrl);


	// ���[���h���W�ւ̕ϊ��͉��ʏ���ݒ肵�Ă���s���I�I

	//// Ground�̈ʒu��傫���𒲐�
	/*m_Position.y = -20.0f;
	m_Scale.x = 20.0f;
	m_Scale.z = 20.0f;*/

	//// ���_����ϊ�
	//Matrix r = Matrix::CreateFromYawPitchRoll(
	//	m_Rotation.y,
	//	m_Rotation.x,
	//	m_Rotation.z);

	//Matrix t = Matrix::CreateTranslation(
	//	m_Position.x,
	//	m_Position.y,
	//	m_Position.z);

	//Matrix s = Matrix::CreateScale(
	//	m_Scale.x,
	//	m_Scale.y,
	//	m_Scale.z);

	//Matrix worldmtx = s * r * t;	// WorldMatrix�F���E�̒��̎����̏����������s��
	//// ���_�������[�v
	//for (int i = 0; i < m_Vertices.size(); i++) {
	//	m_Vertices[i].position = Vector3::Transform(m_Vertices[i].position, worldmtx);
	//	m_Vertices[i].normal = Vector3::Transform(m_Vertices[i].normal, worldmtx);
	//}
}


//=======================================
//�X�V����
//=======================================
void Ground::Update()
{
	/*m_Position.y = -20;
	m_Scale.x = 3;
	m_Scale.z = 3;*/

}

//=======================================
//�`�揈��
//=======================================
void Ground::Draw()
{
	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll(
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	Matrix worldmtx;		// WorldMatrix�F���E�̒��̎����̏����������s��
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// �g�|���W�[���Z�b�g�i�v���~�e�B�u�^�C�v�j
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();

	m_Material->SetGPU();

	//! �J�����ݒ���w��
	m_Camera->SetCamera(0);

	devicecontext->DrawIndexed(
		6 * m_SizeX * m_SizeZ,		// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ̂łS�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);
}

//=======================================
//�I������
//=======================================
void Ground::Uninit()
{

}

void Ground::SetImage(const char* _Filepath)
{
	// �ǂݍ��މ摜�̃t�@�C���p�X
	const char* filename = _Filepath;

	// �摜�f�[�^���i�[����|�C���^
	unsigned char* imageData = nullptr;
	int width, height, channels;

	// �O���[�X�P�[���i�P�`���l���j�ŉ摜��ǂݍ���
	imageData = stbi_load(filename, &width, &height, &channels, 1);
	if (imageData) {
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {

				int picX = x * (float)width / m_SizeX;
				int picY = z * (float)height / m_SizeZ;
				unsigned char pixelValue = imageData[picY * width + picX];
				float h = (float)pixelValue / 15.0f;	// Y���W
				int n = z * m_SizeZ * 6 + x * 6;
				m_Vertices[n + 0].position.y = h;			// 0�Ԗڂ̒��_��y���W��������
				// ���ׂ̎l�p�̒��_
				if (x != 0)m_Vertices[n - 2].position.y = h;
				if (x != 0)m_Vertices[n - 5].position.y = h;

				if (z != 0)m_Vertices[n - m_SizeX * 6 + 2].position.y = h;
				if (z != 0)m_Vertices[n - m_SizeX * 6 + 3].position.y = h;

				if (x != 0 && z != 0)m_Vertices[n - m_SizeX * 6 - 1].position.y = h;
				// if����{}�̏ȗ��́A���߂ďo�Ă���";"�܂ł������Ƃ��ăJ�E���g�����
			}
		}

		// ���_���Ƃ̖@����ێ�����z��
		std::vector<Vector3> vertexNormals(m_Vertices.size(), Vector3(0.0f, 0.0f, 0.0f));

		// �l�p�`���Ƃ̖@���x�N�g�����X�V
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {
				// �l�p�`���\�����钸�_�f�[�^�͈ꎟ���z��ŘA�����ĊǗ�����Ă���
				// �z����̂ǂ̒��_�i�C���f�b�N�X�j����v�Z���邩�����߂�
				int n = z * m_SizeZ * 6 + x * 6;

				// 0�Ԗڂ̒��_���瑼��2���_�ւ̃x�N�g�����v�Z(2�ӕ��ŏ\�����O�p�`�̖ʂ̒�`�͒��_�P�Ƃ��̒��_��ʂ�Q�̃x�N�g���ł��邽��)
				Vector3 v1 = m_Vertices[n + 1].position - m_Vertices[n + 0].position;
				Vector3 v2 = m_Vertices[n + 2].position - m_Vertices[n + 0].position;
				Vector3 normal = v1.Cross(v2);		// �O�ςŖ@�����v�Z
				normal.Normalize();					// ���K��
				m_Vertices[n + 0].normal = normal;
				m_Vertices[n + 1].normal = normal;
				m_Vertices[n + 2].normal = normal;

				// �e���_�ɖ@�������Z
				vertexNormals[n + 0] += normal;
				vertexNormals[n + 1] += normal;
				vertexNormals[n + 2] += normal;

				// 2�̃x�N�g�����v�Z
				v1 = m_Vertices[n + 4].position - m_Vertices[n + 3].position;
				v2 = m_Vertices[n + 5].position - m_Vertices[n + 3].position;
				normal = v1.Cross(v2);				// �O�ςŖ@�����v�Z
				normal.Normalize();					// ���K��
				m_Vertices[n + 3].normal = normal;
				m_Vertices[n + 4].normal = normal;
				m_Vertices[n + 5].normal = normal;

				// �e���_�ɖ@�������Z
				vertexNormals[n + 3] += normal;
				vertexNormals[n + 4] += normal;
				vertexNormals[n + 5] += normal;
			}
		}

		// �o���o���̌����������Ă���@���̌����̕��ς�����Ċe���_�ɑ��
		// ���n�ʂ̂P�̒��_�̖@���̌��������ꂳ��A�V�F�[�f�B���O���Y��ɂȂ�
		// ���_�@���𐳋K�����Đݒ�
		for (size_t i = 0; i < m_Vertices.size(); i++) {
			vertexNormals[i].Normalize();		// �@���𐳋K��
			m_Vertices[i].normal = vertexNormals[i];

		}

		// �����������
		stbi_image_free(imageData);
	}

	// ���_�o�b�t�@��������
	m_VertexBuffer.Modify(m_Vertices);


	// Ground�̈ʒu��傫���𒲐�
	m_Position.y = -20.0f;
	m_Scale.x = 20.0f;
	m_Scale.z = 20.0f;

	// ���_����ϊ�
	Matrix r = Matrix::CreateFromYawPitchRoll(
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	Matrix worldmtx;		// WorldMatrix�F���E�̒��̎����̏����������s��
	worldmtx = s * r * t;

	// ���_�������[�v
	for (int i = 0; i < m_Vertices.size(); i++) {
		m_Vertices[i].position = Vector3::Transform(m_Vertices[i].position, worldmtx);
		m_Vertices[i].normal = Vector3::Transform(m_Vertices[i].normal, worldmtx);
	}
}

//=======================================
// ���_�����擾
//=======================================
std::vector<VERTEX_3D> Ground::GetVertices(void)
{
	return m_Vertices;
}