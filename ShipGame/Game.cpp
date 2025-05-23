#include "Game.h"
#include "Renderer.h"

Game* Game::m_Instance;
Scene* Game::m_Scene = nullptr;

// コンストラクタ
Game::Game()
{
	m_Input = std::make_unique<Input>(); //入力処理を作成
	m_Camera = std::make_unique<Camera>(); //カメラを作成
}

// デストラクタ
Game::~Game()
{
	delete m_Scene;
}

// 初期化
void Game::Init()
{
	// オブジェクト作成
	m_Instance = new Game;

	// 描画初期化
	Renderer::Init();

	// カメラ初期化
	m_Instance->m_Camera->Init();
	m_Instance->m_Scene = new TitleScene; //メモリを確保
}

// 更新
void Game::Update()
{
	// シーン更新
	m_Instance->m_Scene->Update();

	// カメラ更新
	m_Instance->m_Camera->Update();

	// 入力処理更新
	m_Instance->m_Input->Update();

	// オブジェクト更新
	for (auto& o : m_Instance->m_Objects)
	{
		o->Update();
	}
}

// 描画
void Game::Draw()
{
	// 描画前処理
	Renderer::Begin();

	// カメラ描画
	m_Instance->m_Camera->Draw();

	// オブジェクト描画
	for (auto& o : m_Instance->m_Objects)
	{
		o->Draw();
	}

	// 描画後処理
	Renderer::End();
}

// 終了処理
void Game::Uninit()
{
	//オブジェクトを全て削除
	m_Instance->DeleteAllObject();

	//オブジェクト終了処理
	//(※DeleteObject関数で実行するように変更）
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}

	// カメラ終了処理
	//m_Instance->m_Camera->Uninit();

	// 描画終了処理
	Renderer::Uninit();
}

// シーンを切り替える
void Game::ChangeScene(SceneName sName)
{
	// 読み込み済みのシーンがあれば削除
	if (m_Instance->m_Scene != nullptr) {
		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch (sName)
	{
	case TITLE:
		m_Instance->m_Scene = new TitleScene; // メモリを確保
		break;
	}
}

// インスタンスを取得
Game* Game::GetInstance()
{
	return m_Instance;
}

// オブジェクトを削除する
void Game::DeleteObject(Object* pt)
{
	if (pt == NULL) return;

	pt->Uninit(); // 終了処理

	// 要素を削除
	m_Instance->m_Objects.erase(
		std::remove_if(
			m_Instance->m_Objects.begin(),
			m_Instance->m_Objects.end(),
			[pt](const std::unique_ptr<Object>& element) {return element.get() == pt; }),
		m_Instance->m_Objects.end());
	m_Instance->m_Objects.shrink_to_fit();
}

// オブジェクトをすべて削除する
void Game::DeleteAllObject()
{
	// オブジェクト終了処理
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}

	m_Instance->m_Objects.clear(); //全て削除
	m_Instance->m_Objects.shrink_to_fit();
}