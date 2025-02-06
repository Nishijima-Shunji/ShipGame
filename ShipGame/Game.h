#pragma once
#include <vector>
#include <memory>
#include "Object.h"

class Game
{
	static Game* m_Instance; // ゲームインスタンス

	std::vector<std::unique_ptr<Object>> m_Objects;

public:
	Game(); // コンストラクタ
	~Game(); // デストラクタ

	static void Init(); // 初期化
	static void Update(); // 更新
	static void Draw(); // 描画
	static void Uninit(); // 終了処理

	static Game* GetInstance();
	void DeleteObject(Object* pt); // オブジェクトを削除する
	void DeleteAllObject(); // オブジェクトをすべて削除する

	//// オブジェクトを追加する
	//template<class T> T* AddObject()
	//{
	//	T* pt = new T(m_Camera.get());
	//	m_Instance->m_Objects.emplace_back(pt);
	//	pt->Init(); // 初期化
	//	return pt;
	//}

	// オブジェクトを取得する
	template<class T> std::vector<T*> GetObjects()
	{
		std::vector<T*> res;
		for (auto& o : m_Instance->m_Objects) {
			// dynamic_castで型をチェック
			if (T* derivedObj = dynamic_cast<T*>(o.get())) {
				res.emplace_back(derivedObj);
			}
		}
		return res;
	}
};

