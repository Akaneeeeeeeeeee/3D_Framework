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
	this->m_Transform.Position.x = _pos.x;
	this->m_Transform.Position.y = _pos.y;
	this->m_Transform.Position.z = _pos.z;
}

/*
* �֐��̌���const�����ꍇ�����̊֐����Ń����o�ϐ�������������i�ҏW����j�����𖳂������Ƃ��ł���
* ���ێ琫���オ��A���̕����Ń����o�ϐ��������������Ă��Ȃ����Ƃ̏ؖ����ł���
*/
// Position�Q�b�^�[
Vector3 Object::GetPosition(void) const {
	return this->m_Transform.Position;
}

//���̂Ƃ���L�q���e�͖���



