#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "input.h"
#include "Game.h"
#include "GolfBall.h"

using namespace DirectX::SimpleMath;
using namespace std;

//// �R���X�g���N�^
//Camera::Camera(const GolfBall& m_golfball) :m_GolfBall(m_golfball) {
//}

//=======================================
//����������
//=======================================
void Camera::Init()
{
	m_Position = Vector3(0.0f, 20.0f, -50.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
	m_CameraDirection = 3.14f;
	m_CameraPitch = 3.14f;
}


//=======================================
//�X�V����
//=======================================
void Camera::Update()
{
	// ���E�L�[�ŉ�]
	/*if (Input::GetKeyPress(VK_LEFT)) {
		m_CameraDirection += 0.02f;
	}
	if (Input::GetKeyPress(VK_RIGHT)) {
		m_CameraDirection -= 0.02f;
	}*/
	if (Input::GetKeyPress(VK_LEFT)) {
		m_CameraDirection -= 0.02f;
	}
	if (Input::GetKeyPress(VK_RIGHT)) {
		m_CameraDirection += 0.02f;
	}
	if (Input::GetKeyPress(VK_UP)) {
		m_CameraPitch += 0.02f;
	}
	if (Input::GetKeyPress(VK_DOWN)) {
		m_CameraPitch -= 0.02f;
	}

	// �S���t�{�[���̈ʒu���擾
	//Vector3 ballpos = m_GolfBall.GetPosition();
	vector<GolfBall*> ballpt = Game::GetInstance()->GetObjects<GolfBall>();
	if (ballpt.size() > 0) {
		Vector3 ballpos = ballpt[0]->GetPosition();

		// �J�����̈ʒu���X�V
		/*m_Position.x = ballpos.x + sin(m_CameraDirection) * 50;
		m_Position.y = ballpos.y + 20;
		m_Position.z = ballpos.z + cos(m_CameraDirection) * 50;*/

		// �c��]�ǉ�ver
		m_Position.x = ballpos.x + cos(m_CameraPitch) * sin(m_CameraDirection) * 50;
		m_Position.y = ballpos.y + sin(m_CameraPitch) * 50 + 20;
		m_Position.z = ballpos.z + cos(m_CameraPitch) * cos(m_CameraDirection) * 50;

		// �J�����̒����_�X�V
		m_Target = ballpos;
	}
}

//=======================================
//�`�揈��
//=======================================
void Camera::Draw()
{
	
}


//=======================================
//�I������
//=======================================
void Camera::Uninit()
{

}

//=======================================
//�v���W�F�N�V�����s����w��
//=======================================
void Camera::SetCamera(int mode)
{
	// 3D
	if (mode == 0) {
		//! �r���[�ϊ���s��쐬
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		//											�ʒu		�ǂ������Ă�H		�Q�[����ʂ̕���
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up);		// ����n�ɂ����@20230511 by suzuki.tomoki
		// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
		// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
		// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
		// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);	
		Renderer::SetViewMatrix(&m_ViewMatrix);

		//! �v���W�F�N�V�����s��̍쐬
		constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);	//! ����p
		float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());		//! �A�X�y�N�g��
		float nearPlane = 1.0f;		//! �j�A�N���b�v
		float farPlane = 10000.0f;	//! �t�@�[�N���b�v
		Matrix projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);			// ����n�ɂ����@20230511 by suzuki.tomoki
		// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
		// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
		// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
		// projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
		Renderer::SetProjectionMatrix(&projectionMatrix);
	}
	else if (mode == 1)
	{
		//! �r���[�ϊ���s��쐬
		Vector3 pos = { 0.0f,0.0f,-10.0f };
		Vector3 tgt = { 0.0f,0.0f,1.0f };
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(pos, tgt, up);
		Renderer::SetViewMatrix(&m_ViewMatrix);

		//! �v���W�F�N�V�����s��̍쐬
		float nearPlane = 1.0f;
		float farPlane = 1000.0f;
		Matrix projectionMatrix = DirectX::XMMatrixOrthographicLH(
			static_cast<float>(Application::GetWidth()),
			static_cast<float>(Application::GetHeight()), nearPlane, farPlane);
		projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);
		Renderer::SetProjectionMatrix(&projectionMatrix);
	}
}
