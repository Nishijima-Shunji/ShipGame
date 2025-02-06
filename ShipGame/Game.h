#pragma once
#include <vector>
#include <memory>
#include "Object.h"

class Game
{
	static Game* m_Instance; // �Q�[���C���X�^���X

	std::vector<std::unique_ptr<Object>> m_Objects;

public:
	Game(); // �R���X�g���N�^
	~Game(); // �f�X�g���N�^

	static void Init(); // ������
	static void Update(); // �X�V
	static void Draw(); // �`��
	static void Uninit(); // �I������

	static Game* GetInstance();
	void DeleteObject(Object* pt); // �I�u�W�F�N�g���폜����
	void DeleteAllObject(); // �I�u�W�F�N�g�����ׂč폜����

	//// �I�u�W�F�N�g��ǉ�����
	//template<class T> T* AddObject()
	//{
	//	T* pt = new T(m_Camera.get());
	//	m_Instance->m_Objects.emplace_back(pt);
	//	pt->Init(); // ������
	//	return pt;
	//}

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

