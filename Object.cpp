#include "Object.h"

using namespace DirectX::SimpleMath;

/**
 * @brief �R���X�g���N�^
 * @param cam �J�����̃|�C���^
*/
Object::Object(Camera* cam) :m_Camera(cam) {

}

/**
 * @brief �f�X�g���N�^
*/
Object::~Object() {

}

// Position�Z�b�^�[
void Object::SetPosition(const Vector3& _pos) {
	m_Position.x = _pos.x;
	m_Position.y = _pos.y;
	m_Position.z = _pos.z;
}

/*
* �֐��̌���const�����ꍇ�����̊֐����Ń����o�ϐ�������������i�ҏW����j�����𖳂������Ƃ��ł���
* ���ێ琫���オ��A���̕����Ń����o�ϐ��������������Ă��Ȃ����Ƃ̏ؖ����ł���
*/
// Position�Q�b�^�[
Vector3 Object::GetPosition(void) const {
	return m_Position;
}

//���̂Ƃ���L�q���e�͖���



