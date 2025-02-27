#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Object.h"

class Ground : public Object
{
	// 描画の為の情報（メッシュに関わる情報）
	IndexBuffer	 m_IndexBuffer; // インデックスバッファ
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // 頂点バッファ

	// 描画の為の情報（見た目に関わる部分）
	//Shader m_Shader; // シェーダー
	Texture m_Texture;	//テクスチャ
	std::unique_ptr<Material> m_Materiale;	//マテリアル

	int m_SizeX;	//横サイズ
	int m_SizeZ;	//縦サイズ
	std::vector<VERTEX_3D> m_Vertices;	//頂点情報

	//=====================================
	float currentTime = 0.0f;

	struct TimerBufferType {
		float Timer;       // グローバルタイマー
		float Padding[3];  // パディングを追加（DirectXでは16バイト単位）
	};


public:
	Ground(Camera* cam);	//コンストラクタ
	~Ground();				//デストラクタ

	void Init();
	void Draw();
	void Update();
	void Uninit();

	//頂点情報を取得
	std::vector<VERTEX_3D> GetVertices();
};

