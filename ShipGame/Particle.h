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
	 Vector3 position; //���W
	 Vector3 velocity; //���x
	 Vector3 force;    //��
	 float   density;  //���x
	 float   pressure; //����

	 // ���x
	 const float h = 0.012;					//�e�����a
	 const float particleMass = 0.0002f;	//���q�̎���
	 const float densityCoef = particleMass * 315.0f / (64.0f * DirectX::XM_PI * pow(h, 9));	//���x�v�Z�Ŏg��

	 // ����
	 const float pressureStiffness = 3.0f;	//���͌W��
	 const float restDensity = 1000.0f;		//�Î~���x

	 // ���͍�
	 const float viscosity = 0.1f; // �S���W��

	 std::vector<VERTEX_3D> m_Vertex;
	 VertexBuffer<VERTEX_3D> m_VertexBuffer;
	 Shader m_Shader;
	 Texture m_Texture;
	 std::unique_ptr<Material> m_Material;

public:
	Particle(Camera* cam);	//�R���X�g���N�^
	~Particle();			//�f�X�g���N�^

	void Init();
	void Draw();
	void Update();
	void Uninit();

	// SPH�i�����j�̌v�Z
	void CalcDensity(std::vector<Particle*>&);		// ���x�v�Z
	void CalcPressure(std::vector<Particle*>&);		// ���͌v�Z
	void CalcForce(std::vector<Particle*>&);		// ���͍��v�Z
	void ApplyBoundaryForce(const Vector3& minBound, const Vector3& maxBound, float boundaryStiffness);		// �ǂ̓����蔻��(���E����)
};

