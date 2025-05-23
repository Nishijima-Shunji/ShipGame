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
	 Vector3 position; //ÀW
	 Vector3 velocity; //¬x
	 Vector3 force;    //Í
	 float   density;  //§x
	 float   pressure; //³Í

	 // §x
	 const float h = 0.012;					//e¿¼a
	 const float particleMass = 0.0002f;	//±qÌ¿Ê
	 const float densityCoef = particleMass * 315.0f / (64.0f * DirectX::XM_PI * pow(h, 9));	//§xvZÅg¤

	 // ³Í
	 const float pressureStiffness = 3.0f;	//³ÍW
	 const float restDensity = 1000.0f;		//Ã~§x

	 // ³Í
	 const float viscosity = 0.1f; // S«W

	 std::vector<VERTEX_3D> m_Vertex;
	 VertexBuffer<VERTEX_3D> m_VertexBuffer;
	 Shader m_Shader;
	 Texture m_Texture;
	 std::unique_ptr<Material> m_Material;

public:
	Particle(Camera* cam);	//RXgN^
	~Particle();			//fXgN^

	void Init();
	void Draw();
	void Update();
	void Uninit();

	// SPHi¨jÌvZ
	void CalcDensity(std::vector<Particle*>&);		// §xvZ
	void CalcPressure(std::vector<Particle*>&);		// ³ÍvZ
	void CalcForce(std::vector<Particle*>&);		// ³ÍvZ
	void ApplyBoundaryForce(const Vector3& minBound, const Vector3& maxBound, float boundaryStiffness);		// ÇÌ½è»è(«E½­)
};

