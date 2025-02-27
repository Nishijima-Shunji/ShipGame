#pragma once
#include "Scene.h"
#include "Object.h"

class TitleScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

	void Init(); // 初期化
	void Uninit(); // 終了処理
public:
	TitleScene();
	~TitleScene();

	void Update();
};

