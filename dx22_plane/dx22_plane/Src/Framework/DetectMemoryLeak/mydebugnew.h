#pragma once

/* MyDbgNew.h
   �O���[�o���� new ���Z�q���I�[�o�[���[�h����
   �N���C�A���g�u���b�N���烁�������m�ۂ���ݒ���`
*/

#ifdef _DEBUG
	// �f�o�b�O�r���h���F
	// new ���Z�q���A�t�@�C�����ƍs�ԍ����t���Ń������m�ۂ���`�ɒu��������
	#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
	// �� _NORMAL_BLOCK �� _CLIENT_BLOCK �ɕύX����ƁA
	//    �������m�ێ�ʂ��u�N���C�A���g�u���b�N�v�ɂł��܂�
#else
	// �����[�X�r���h���F
	// �����u���������A�ʏ�� new ���g��
	#define MYDEBUG_NEW
#endif // _DEBUG

