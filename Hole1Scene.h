#pragma once
#include "Scene.h"
#include "Object.h"

// 1�z�[����
class Hole1Scene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g

	void Init();		// ������
	void Uninit();		// �I������

	int m_Par;			// �p�[�i�W���Ő��j
	int m_StrokeCount;	// ���݂̑Ő�

public:
	Hole1Scene();			// �R���X�g���N�^
	~Hole1Scene();			// �f�X�g���N�^

	void Update();			// �X�V

	int GetTargetScore(void);
	int GetScore(void);	// �X�R�A���擾

};

