#pragma once
#include <iostream>
#include "FadeAnimation.h"
#include "Camera.h"
#include "Input.h"
#include "TitleScene.h"
#include "Hole1Scene.h"
#include "Hole2Scene.h"
#include "Hole3Scene.h"
#include "ResultScene.h"

enum SceneName {
	TITLE,
	HOLE1,
	HOLE2,
	HOLE3,
	/*HOLE4,
	HOLE5,
	HOLE6,
	HOLE7,
	HOLE8,
	HOLE9,*/
	BONUS,
	RESULT
};

class Game
{
public:



private:
	//! �Q�[���N���X����I�u�W�F�N�g�ɃA�N�Z�X���₷�����邽�߂ɃQ�[���N���X�̃C���X�^���X���Q�[���N���X���g�Ɏ�������
	//! ����������ƃQ�b�^�[�֐��łǂ�����ł�Objects�ɃA�N�Z�X���邱�Ƃ��ł���i�H�j
	static Game* m_Instance; // �Q�[���C���X�^���X

	Scene* m_Scene; // �V�[��

	std::vector<std::unique_ptr<Object>> m_Objects; // �I�u�W�F�N�g
	std::unique_ptr<Input> m_Input;  // ���͏���
	std::unique_ptr<Camera> m_Camera; // �J����

	bool Change = false;		// �V�[���؂�ւ��t���O
	bool Changing = false;		// �V�[���J�ڒ��Ǘ��t���O
	//std::unique_ptr<FadeAnimation> m_FadeAnimation;
	SceneName m_NextSceneName;	// ���V�[���̖��O

public:
	Game(); // �R���X�g���N�^
	~Game(); // �f�X�g���N�^

	static void Init(); // ������
	static void Update(); // �X�V
	static void Draw(); // �`��
	static void Uninit(); // �I������
	
	static Game* GetInstance();
	void SetChange(bool _flg);		// �ォ��ǉ�
	bool GetChange(void);			// �ォ��ǉ�
	void SetChanging(bool _flg);	// �ォ��ǉ�
	bool GetChanging(void);			// �ォ��ǉ�

	void ChangeScene(SceneName sName);	// �V�[����ύX
	Camera& GetCamera();				// �J�����擾
	void DeleteObject(Object* pt);		// �I�u�W�F�N�g���폜����
	void DeleteAllObject();				// �I�u�W�F�N�g�����ׂč폜����

	// �I�u�W�F�N�g��ǉ�����(���e���v���[�g�֐��Ȃ̂ł����ɒ��ڋL�q)
	template<class T> T* AddObject()
	{
		T* pt = new T(m_Camera.get());
		m_Instance->m_Objects.emplace_back(pt);
		pt->Init(); // ������
		return pt;
	}

	// �I�u�W�F�N�g���擾����(���e���v���[�g�֐��Ȃ̂ł����ɒ��ڋL�q)
	template<class T> std::vector<T*> GetObjects()
	{
		std::vector<T*> res;
		for (auto& o : m_Instance->m_Objects) {
			// dynamic_cast�Ō^���`�F�b�N
			if (T* derivedObj = dynamic_cast<T*>(o.get())) {
				res.emplace_back(derivedObj);
			}
		}
		return res;
	}

};
