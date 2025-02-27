#pragma once
#include "Scene.h"
#include "Object.h"

class TitleScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g

	void Init(); // ������
	void Uninit(); // �I������
public:
	TitleScene();
	~TitleScene();

	void Update();
};

