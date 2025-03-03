#pragma once

#include	<SimpleMath.h>

//-----------------------------------------------------------------------------
//Camera�N���X
//-----------------------------------------------------------------------------
class Camera {
private:
	// ���W�i�ǂ��ɂ���H�j
	DirectX::SimpleMath::Vector3	m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3	m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3	m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// �^�[�Q�b�g�i�ǂ������Ă�H�j
	DirectX::SimpleMath::Vector3	m_Target{};
	DirectX::SimpleMath::Matrix		m_ViewMatrix{};

	float m_CameraDirection = 0;	// �J�����̕���
	float m_CameraPitch = 0;

public:
	
	void Init();
	void Update();
	void Draw();
	void Uninit();

	void SetCamera(int mode);
};