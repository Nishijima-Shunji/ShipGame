#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Input.h"
#include "Scene.h"

#include "TitleScene.h"

enum SceneName {
	TITLE,
	STAGE1,
	RESULT
};

class Game
{
	static Game* m_Instance; // �Q�[���C���X�^���X
	static Scene* m_Scene;

	std::vector<std::unique_ptr<Object>> m_Objects;
	std::unique_ptr<Input> m_Input;  // ���͏���
	std::unique_ptr<Camera> m_Camera; // �J����

public:
	Game();	 // �R���X�g���N�^
	~Game(); // �f�X�g���N�^

	static void Init();		// ������
	static void Update();	// �X�V
	static void Draw();		// �`��
	static void Uninit();	// �I������

	void ChangeScene(SceneName sName); // �V�[����ύX

	Camera& GetCamera(); // �J�����擾

	static Game* GetInstance();
	void DeleteObject(Object* pt);	// �I�u�W�F�N�g���폜����
	void DeleteAllObject();			// �I�u�W�F�N�g�����ׂč폜����

	// �I�u�W�F�N�g��ǉ�����
	template<class T> T* AddObject()
	{
		T* pt = new T(m_Camera.get());
		m_Instance->m_Objects.emplace_back(pt);
		pt->Init(); // ������
		return pt;
	}

	// �I�u�W�F�N�g���擾����
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

