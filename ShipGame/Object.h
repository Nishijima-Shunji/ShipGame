#pragma once
#include <SimpleMath.h>
#include "Shader.h"
#include "Camera.h"

using Vector3 = DirectX::SimpleMath::Vector3;

class Object
{
protected:
	//カメラ
	Camera* m_Camera;
	// 描画の為の情報（見た目に関わる部分）
	Shader m_Shader; // シェーダー

	Vector3 m_Position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Scale = Vector3(1.0f, 1.0f, 1.0f);
public:
	Object(Camera* cam);	//コンストラクタ
	virtual ~Object();	//デストラクタ
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

	void SetPosition(const Vector3& pos) {
		m_Position.x = pos.x;
		m_Position.y = pos.y;
		m_Position.z = pos.z;
	};
	Vector3 GetPosition() const { return m_Position; };
	Vector3 GetRotation() const { return m_Rotation; };
};

