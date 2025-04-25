#pragma once
#include "Scene.h"
#include "Object.h"
#include "Particle.h"

class TitleScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト
	std::vector<Particle*> particle;

	void Init(); // 初期化
	void Uninit(); // 終了処理
public:
	TitleScene();
	~TitleScene();

	void Update();
};

