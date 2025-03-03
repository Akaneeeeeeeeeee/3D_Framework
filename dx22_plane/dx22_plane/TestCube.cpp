#include	"TestCube.h"

using namespace DirectX::SimpleMath;

//=======================================
//����������
//=======================================
void TestCube::Init()
{
	// ���_�f�[�^
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(24);
	
	// ���_���W�ݒ�
	// ���(1)
	vertices[0].position = Vector3(-10, 10, 10);
	vertices[1].position = Vector3( 10, 10, 10);
	vertices[2].position = Vector3(-10, 10, -10);
	vertices[3].position = Vector3( 10, 10, -10);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);			// 0~1��uv���W��3�������邽��1/3
	vertices[1].uv = Vector2(1 / 3.0, 0);	// 1/3����int�^�̌v�Z�ɂȂ�̂�float�ɂ���
	vertices[2].uv = Vector2(0, 1 / 2.0);
	vertices[3].uv = Vector2(0.33, 0.5);

	vertices[0].normal = Vector3(0, 1, 0);
	vertices[1].normal = Vector3(0, 1, 0);
	vertices[2].normal = Vector3(0, 1, 0);
	vertices[3].normal = Vector3(0, 1, 0);

	// ��O��(2)
	vertices[4].position = Vector3(-10, 10, -10);
	vertices[5].position = Vector3( 10, 10, -10);
	vertices[6].position = Vector3(-10, -10, -10);
	vertices[7].position = Vector3( 10, -10, -10);

	vertices[4].color = Color(1, 1, 1, 1);
	vertices[5].color = Color(1, 1, 1, 1);
	vertices[6].color = Color(1, 1, 1, 1);
	vertices[7].color = Color(1, 1, 1, 1);
	
	vertices[4].uv = Vector2(0.33, 0);
	vertices[5].uv = Vector2(0.66, 0);
	vertices[6].uv = Vector2(0.33, 0.5);
	vertices[7].uv = Vector2(0.66, 0.5);

	vertices[4].normal = Vector3(0, 0, -1);
	vertices[5].normal = Vector3(0, 0, -1);
	vertices[6].normal = Vector3(0, 0, -1);
	vertices[7].normal = Vector3(0, 0, -1);

	// ����(6)
	vertices[8].position = Vector3(-10, -10, -10);
	vertices[9].position = Vector3( 10, -10, -10);
	vertices[10].position = Vector3(-10, -10, 10);
	vertices[11].position = Vector3( 10, -10, 10);

	vertices[8].color = Color(1, 1, 1, 1);
	vertices[9].color = Color(1, 1, 1, 1);
	vertices[10].color = Color(1, 1, 1, 1);
	vertices[11].color = Color(1, 1, 1, 1);

	vertices[8].uv = Vector2(0.66, 0.5);
	vertices[9].uv = Vector2(1, 0.5);
	vertices[10].uv = Vector2(0.66, 1);
	vertices[11].uv = Vector2(1, 1);

	vertices[8].normal = Vector3(0, -1, 0);
	vertices[9].normal = Vector3(0, -1, 0);
	vertices[10].normal = Vector3(0, -1, 0);
	vertices[11].normal = Vector3(0, -1, 0);

	// ����(5)
	vertices[12].position = Vector3(-10, -10, 10);
	vertices[13].position = Vector3( 10, -10, 10);
	vertices[14].position = Vector3(-10, 10, 10);
	vertices[15].position = Vector3( 10, 10, 10);

	vertices[12].color = Color(1, 1, 1, 1);
	vertices[13].color = Color(1, 1, 1, 1);
	vertices[14].color = Color(1, 1, 1, 1);
	vertices[15].color = Color(1, 1, 1, 1);

	vertices[12].uv = Vector2(0.33, 0.5);
	vertices[13].uv = Vector2(0.66, 0.5);
	vertices[14].uv = Vector2(0.33, 1);
	vertices[15].uv = Vector2(0.66, 1);

	vertices[12].normal = Vector3(0, 0, 1);
	vertices[13].normal = Vector3(0, 0, 1);
	vertices[14].normal = Vector3(0, 0, 1);
	vertices[15].normal = Vector3(0, 0, 1);

	// �E��(3)
	vertices[16].position = Vector3(10, 10, -10);
	vertices[17].position = Vector3(10, 10, 10);
	vertices[18].position = Vector3(10, -10, -10);
	vertices[19].position = Vector3(10, -10, 10);

	vertices[16].color = Color(1, 1, 1, 1);
	vertices[17].color = Color(1, 1, 1, 1);
	vertices[18].color = Color(1, 1, 1, 1);
	vertices[19].color = Color(1, 1, 1, 1);

	vertices[16].uv = Vector2(0.66, 0);
	vertices[17].uv = Vector2(1, 0);
	vertices[18].uv = Vector2(0.66, 0.5);
	vertices[19].uv = Vector2(1, 0.5);

	vertices[16].normal = Vector3(1, 0, 0);
	vertices[17].normal = Vector3(1, 0, 0);
	vertices[18].normal = Vector3(1, 0, 0);
	vertices[19].normal = Vector3(1, 0, 0);

	// ����(4)
	vertices[20].position = Vector3(-10, 10, 10);
	vertices[21].position = Vector3(-10, 10, -10);
	vertices[22].position = Vector3(-10, -10, 10);
	vertices[23].position = Vector3(-10, -10, -10);

	vertices[20].color = Color(1, 1, 1, 1);
	vertices[21].color = Color(1, 1, 1, 1);
	vertices[22].color = Color(1, 1, 1, 1);
	vertices[23].color = Color(1, 1, 1, 1);

	vertices[20].uv = Vector2(0, 0.5);
	vertices[21].uv = Vector2(0.33, 0.5);
	vertices[22].uv = Vector2(0, 1);
	vertices[23].uv = Vector2(0.33, 1);

	vertices[20].normal = Vector3(-1, 0, 0);
	vertices[21].normal = Vector3(-1, 0, 0);
	vertices[22].normal = Vector3(-1, 0, 0);
	vertices[23].normal = Vector3(-1, 0, 0);

	// ���_�o�b�t�@����
	m_VertexBuffer.Create(vertices);

	// �C���f�b�N�X�o�b�t�@�i���_�̌��ѕ��̏��ԃf�[�^�j����
	std::vector<unsigned int> indices;
	indices.resize(36);

	// 5�̒��_�����ꂼ�ꉽ�Ԗڂ̒��_�Ƃ��邩
	// �����v����ɂ���Ɨ����\���ɂȂ�J�����O�ݒ�ŕ`�悳��Ȃ��Ȃ��Ă��܂�
	
	indices = {
		// ��ʍ�
		0,1,2,
		// ��ʉE
		1,3,2,
		// ��O�ʍ�
		4,5,6,
		// ��O�ʉE
		5,7,6,
		// ���ʍ�
		8,9,10,
		// ���ʉE
		9,11,10,
		// ���ʍ�
		12,13,14,
		// ���ʉE
		13,15,14,
		// �E�ʍ�
		16,17,18,
		// �E�ʉE
		17,19,18,
		// ���ʍ�
		20,21,22,
		// ���ʉE
		21,23,22
	};
	

	// �C���f�b�N�X�o�b�t�@����
	m_IndexBuffer.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	//m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	// �e�N�X�`�������[�h
	bool sts = m_Texture.Load("assets/texture/dice.png");
	assert(sts == true);
}


//=======================================
//�X�V����
//=======================================
void TestCube::Update()
{
	m_Rotation.x += 0.01f;
	m_Rotation.y += 0.01f;
	m_Rotation.z += 0.01f;

}

//=======================================
//�`�揈��
//=======================================
void TestCube::Draw()
{
	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll( m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation( m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale( m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// �g�|���W�[�i���_�̌��ѕ��̋K���j���Z�b�g�i�v���~�e�B�u�^�C�v�j
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		36,							// �`�悷��C���f�b�N�X���i������(�|���S��1�ʂɂ�3)�Ȃ̂�36�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);
}

//=======================================
//�I������
//=======================================
void TestCube::Uninit()
{

}