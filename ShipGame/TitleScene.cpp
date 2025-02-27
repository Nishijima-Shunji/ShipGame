#include "TitleScene.h"
#include "Texture2D.h"
#include "Game.h"

TitleScene::TitleScene() {
	Init();
}

TitleScene::~TitleScene() {
	Uninit();
}

void TitleScene::Init() {
	m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());
	Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/background1.png");
	pt->SetPosition(0.0f, 0.0f, 0.0f);
	pt->SetScale(300.0f, 300.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt);
}

void TitleScene::Uninit() {
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
}

void TitleScene::Update() {
	
}