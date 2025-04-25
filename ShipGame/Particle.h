#pragma once
#include "Object.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include <SimpleMath.h>
#include <DirectXMath.h>

class Particle : public Object
{
private:
	 Vector3 position; //座標
	 Vector3 velocity; //速度
	 Vector3 force;    //力
	 float   density;  //密度
	 float   pressure; //圧力

	 // 密度
	 const float h = 0.012;					//影響半径
	 const float particleMass = 0.0002f;	//粒子の質量
	 const float densityCoef = particleMass * 315.0f / (64.0f * DirectX::XM_PI * pow(h, 9));	//密度計算で使う

	 // 圧力
	 const float pressureStiffness = 3.0f;	//圧力係数
	 const float restDensity = 1000.0f;		//静止密度

	 // 圧力項
	 const float viscosity = 0.1f; // 粘性係数

	 std::vector<VERTEX_3D> m_Vertex;
	 VertexBuffer<VERTEX_3D> m_VertexBuffer;
	 Shader m_Shader;
	 Texture m_Texture;
	 std::unique_ptr<Material> m_Material;

public:
	Particle(Camera* cam);	//コンストラクタ
	~Particle();			//デストラクタ

	void Init();
	void Draw();
	void Update();
	void Uninit();

	// SPH（物理）の計算
	void CalcDensity(std::vector<Particle*>&);		// 密度計算
	void CalcPressure(std::vector<Particle*>&);		// 圧力計算
	void CalcForce(std::vector<Particle*>&);		// 圧力項計算
	void ApplyBoundaryForce(const Vector3& minBound, const Vector3& maxBound, float boundaryStiffness);		// 壁の当たり判定(境界反発)
};

