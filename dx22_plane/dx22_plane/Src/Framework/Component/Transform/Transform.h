#pragma once
#include "../../../Entry/main.h"


using namespace DirectX::SimpleMath;

// TODO:2024/11/27 ����\���̂ł������I�I�I�I�I�I�I
// ��Transform�͂����܂Ńf�[�^�̎��܂Ƃ߁��킴�킴�N���X�ɂ��Čp�������Ă��܂��Ɛe�q�֌W���[���Ȃ肷���Đ�΂�₱�����Ȃ邩�炱��͂�߂�ׂ�
// �N���X�e���v���[�g�Ƃ��W�����C�u�����A�X�}�[�g�|�C���^�̕׋����K�v���� std::vector�Ƃ��ŃR���|�[�l���g���D���Ȃ��������Ƃ��ł�����

/// <summary>
/// Transform�N���X�F�S�ẴI�u�W�F�N�g�������Ă�����i�����ł͐��l�݂̂������j
/// �E���W
/// �E��]
/// �E�傫��
/// �̏�������
/// 
/// �e���l�̍s��ϊ��͖��t���[���s�����X�V�͕s�v
/// ���[���h�s��ւ̕ϊ���Transform���ōs��
/// </summary>

struct Transform
{
public:
	Transform() :Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Scale(75.0f, 75.0f, 0.0f) {};
	Transform(const Vector3& _pos, const Vector3& _rot, const Vector3& _scale) : Position(_pos), Rotation(_rot), Scale(_scale) {};
	~Transform() {};
	
	// �X�V����ׂ��Ȃ̂̓R���|�[�l���g�Ȃ̂ł����ɍX�V�͂���Ȃ��H
	// ��conio��vector�Ƃ��Ɠ����m���H
	Vector3 Position;	// ���W
	Vector3 Rotation;	// �p�x
	Vector3 Scale;	// �傫��
};

