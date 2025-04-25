#pragma once
#include "Scene.h"
#include "Object.h"
#include "Particle.h"

class TitleScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g
	std::vector<Particle*> particle;

	void Init(); // ������
	void Uninit(); // �I������
public:
	TitleScene();
	~TitleScene();

	void Update();
};

