#pragma once

#include "../../../Framework/Buffer/VertexBuffer.h"
#include "../../../Framework/Buffer/IndexBuffer.h"
#include "../../../Framework/Shader/Shader.h"
#include "../../Camera/Camera.h"
#include "../../../Framework/Component/Transform/Transform.h"
#include "../../../Framework/Component/IComponent/IComponent.h"

using namespace DirectX::SimpleMath;

class Object {
protected:
	// SRT���i�p�����j
	//DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);	// Position(Translation)
	//DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	//DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	Transform m_Transform = Transform(Vector3(0.0f, 0.0f, 0.0f) ,Vector3(0.0f, 0.0f, 0.0f) ,Vector3(1.0f, 1.0f, 1.0f)); // SRT�����Ǘ�

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	Shader m_Shader; // �V�F�[�_�[

	// �J����
	Camera* m_Camera;

	// �R���|�[�l���g
	std::vector<IComponent> m_Components; // �R���|�[�l���g�̃��X�g

public:

	Object(Camera* cam);	//! �R���X�g���N�^
	virtual ~Object();		//! �f�X�g���N�^

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

	// position�̃Z�b�^�[�Q�b�^�[
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	DirectX::SimpleMath::Vector3 GetPosition(void) const;
};
