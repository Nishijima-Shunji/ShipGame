#include "TitleScene.h"
#include "Texture2D.h"
#include "Game.h"
#include "Ground.h"


TitleScene::TitleScene() {
	Init();
}

TitleScene::~TitleScene() {
	Uninit();
}

void TitleScene::Init() {
	//m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>());

	/*Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/background1.png");
	pt->SetPosition(0.0f, 0.0f, 0.0f);
	pt->SetScale(300.0f, 300.0f, 0.0f);
	m_MySceneObjects.emplace_back(pt);*/

	// ���q����
	for (int i = 0; i < 100; i++) {
		Particle* pt = Game::GetInstance()->AddObject<Particle>();
		particle.push_back(pt);
		m_MySceneObjects.emplace_back(pt);
	}
}

void TitleScene::Uninit() {
	// ���̃V�[���̃I�u�W�F�N�g���폜����
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
	for (auto& p : particle) {
		Game::GetInstance()->DeleteObject(p);
	}
	particle.clear();
}

void TitleScene::Update() {
	// �e���q�̌v�Z
	for (auto& p : particle) {
		p->CalcDensity(particle);
	}
	for (auto& p : particle) {
		p->CalcPressure(particle);
	}
	for (auto& p : particle) {
		p->CalcForce(particle);
	}
	// �v�Z���ʂ���ɓ�����
	for (const auto obj : particle) {
		obj->Update();
	}
}