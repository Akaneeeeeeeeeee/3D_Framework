#include <memory>
#include "GolfBall.h"
#include "StaticMesh.h"
#include "utility.h"
#include "Collision.h"
#include "input.h"
#include "Game.h"
#include "Ground.h"
#include "Pole.h"

using namespace std;
using namespace DirectX::SimpleMath;

/**
 * @brief �R���X�g���N�^
 * @param cam ���N���X�ł���I�u�W�F�N�g�N���X�̃J���������������邽�߂̃J�����^�|�C���^
*/
GolfBall::GolfBall(Camera* cam) :Object(cam) {

}

/**
 * @brief �f�X�g���N�^
*/
GolfBall::~GolfBall() {

}

void GolfBall::Init()
{
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	//3D���f���f�[�^
	std::u8string modelFile = u8"assets/model/golfball2/golf_ball.obj";

	//�e�N�X�`���f�B���N�g��
	std::string texDirectory = "assets/model/golfball2";

	//Mesh��ǂݍ���
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

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
	m_Scale.x = 1;
	m_Scale.y = 1;
	m_Scale.z = 1;

	// �ŏ��ɑ��x��^����(�ŏ���1�t���[��������ǂꂭ�炢�̑��x��)
	//m_Velocity.x = 0.5f;
	m_Position = { 0.0f,0.0f,0.0f };
}

void GolfBall::Update()
{
	if (m_State != 0) return;		// �Î~��ԂȂ�return

	Vector3 oldPos = m_Position;	// 1�t���[���O�̈ʒu���L�����Ă���

	// ���x��0�ɋ߂Â������~
	if (m_Velocity.LengthSquared() < 0.03f) {
		m_StopConut++;
		//m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	}
	else {
		m_StopConut = 0;
		// �����x(1�t���[��������ǂꂭ�炢�������邩)
		float decelerationPower = 0.05f;		// ���l0.005f
		Vector3 deceleration = -m_Velocity;		// ���x�̋t�x�N�g�����v�Z
		deceleration.Normalize();				// �x�N�g���𐳋K��
		m_Acceleration = deceleration * decelerationPower;

		// �����x�𑬓x�ɉ��Z(�t�����ɐi�����Ƃ���)
		m_Velocity += m_Acceleration;
	}

	// 10�t���[���A���łقƂ�Ǔ����Ă��Ȃ���ΐÎ~��Ԃ�
	if (m_StopConut > 10) {
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_State = 1;		// �Î~���
	}

	// �d��
	const float gravity = 0.098f;		// �d�͂�9.8f
	m_Velocity.y -= gravity;

	// ���x�����W�ɉ��Z
	m_Position += m_Velocity;

	float radius = 2.0f;

	// Ground�̒��_�f�[�^���擾;
	//std::vector<VERTEX_3D> vertices = m_Ground->GetVertices();
	vector<Ground*> grounds = Game::GetInstance()->GetObjects<Ground>();
	vector<VERTEX_3D> vertices;
	for (auto g: grounds )
	{
		vector<VERTEX_3D> vecs = g->GetVertices();
		for (auto& v : vecs)
		{
			vertices.emplace_back(v);
		}
	}

	float moveDistance = 9999;		// �ړ�����
	Vector3 contactPoint;			// �ڐG�_
	Vector3 normal;

	// ���̂̐����ƃ|���S���̓����蔻��
	bool line_segment = false;
	for (int i = 0; i < vertices.size(); i += 3)
	{
		// 3�p�`�|���S��
		Collision::Polygon collisionPolygon = {
			vertices[i + 0].position,
			vertices[i + 1].position,
			vertices[i + 2].position
		};

		Vector3 cp;			// �ڐG�_
		Collision::Segment collisionSegment = { oldPos,m_Position };
		if (Collision::CheckHit(collisionSegment, collisionPolygon, cp))
		{
			float md = 0;
			Vector3 np = Collision::moveSphere(collisionSegment,radius, collisionPolygon, cp, md);
			if (moveDistance > md)
			{
				moveDistance = md;
				m_Position = np;
				contactPoint = cp;
				normal = Collision::GetNormal(collisionPolygon);
			}
			line_segment = true;
		}
	}

	// ���̂ƃ|���S���̓����蔻��
	if (!line_segment) {
		for (int i = 0; i < vertices.size(); i += 3)
		{
			// 3�p�`�|���S��
			Collision::Polygon collisionPolygon = {
				vertices[i + 0].position,
				vertices[i + 1].position,
				vertices[i + 2].position
			};

			Vector3 cp;			// �ڐG�_
			Collision::Sphere collisionSphere = { m_Position,radius };
			if (Collision::CheckHit(collisionSphere, collisionPolygon, cp))
			{
				float md = 0;
				Vector3 np = Collision::moveSphere(collisionSphere, collisionPolygon, cp);
				md = (np - oldPos).Length();
				if (moveDistance > md)
				{
					moveDistance = md;
					m_Position = np;
					contactPoint = cp;
					normal = Collision::GetNormal(collisionPolygon);
				}
			}
		}
	}

	// �����������Ă�����
	if (moveDistance != 9999)
	{
		m_Velocity.y = -gravity;

		//! �{�[���̑��x�x�N�g���̖@�����������Ɛڐ����������𕪉�
		float velocityNormal = Collision::Dot(m_Velocity, normal);
		Vector3 v1 = velocityNormal * normal;		//! �@����������
		Vector3 v2 = m_Velocity - v1;				//! �ڐ���������

		//! �����W��
		const float restitution = 0.05f;
		
		//! ���˃x�N�g�����v�Z
		Vector3 reflectedVelocity = v2 - restitution * v1;

		//! �{�[���̑��x���X�V
		m_Velocity = reflectedVelocity;
	}

	// ���ɗ��������̓��X�|�[��
	if (m_Position.y < -100)
	{
		m_Position = Vector3(0.0f, 50.0f, 0.0f);
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	}

	// �|�[���̈ʒu���擾
	vector<Pole*> pole = Game::GetInstance()->GetObjects<Pole>();
	if (pole.size() > 0) {
		Vector3 polePos = pole[0]->GetPosition();
		Collision::Sphere ballCollision = { m_Position,radius };	// �S���t�{�[���̓����蔻��
		Collision::Sphere poleCollision = { polePos,0.5f };			// �|�[���̓����蔻��
		if (Collision::CheckHit(ballCollision, poleCollision))
		{
			m_State = 2;	// �J�b�v�C��
		}
	}
}

void GolfBall::Draw()
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

/**
 * @brief �I������
*/
void GolfBall::Uninit()
{

}

// ��Ԃ̐ݒ�E�擾
void GolfBall::SetState(int s) { m_State = s; }
int GolfBall::GetState(void) { return m_State; }

// �V���b�g
void GolfBall::Shot(Vector3 v) { m_Velocity = v; }		// �{�[���ړ���, 1:�����I��, 2:�p���[�I��
