#include "Particle.h"

Particle::Particle(Camera* cam) : Object(cam) {

}

Particle::~Particle() {

}

void Particle::Init() {
    // ���_1������`�i�p�[�e�B�N����1�_�Ƃ��ĕ`��j
    m_Vertex.position = Vector3(0, 0, 0);
    m_Vertex.color = Color(1, 1, 1, 1);  // ��
    m_Vertex.uv = Vector2(0, 0);
    m_Vertex.normal = Vector3(0, 1, 0);

    std::vector<VERTEX_3D> verts = { m_Vertex };
    m_VertexBuffer.Create(verts);

    // �V�F�[�_
    m_Shader.Create("shader/unlitVS.hlsl", "shader/unlitPS.hlsl");

    // �e�N�X�`���i�C�Ӂj
    m_Texture.Load("assets/texture/particle.png");

    // �}�e���A��
    m_Material = std::make_unique<Material>();
    MATERIAL mtrl;
    mtrl.Diffuse = Color(1, 1, 1, 1);
    mtrl.Shiness = 1;
    mtrl.TextureEnable = true;
    m_Material->Create(mtrl);
}

void Particle::Update() {
    

    float dt = 0.016f; // ���ԃX�e�b�v�i�b�j

    // �����x a = f / ��
    Vector3 acceleration = force / density;

    // ���x�X�V
    velocity += acceleration * dt;

    // �ʒu�X�V
    position += velocity * dt;
}

void Particle::Draw() {

}

void Particle::Uninit() {

}

//���q�̖��x�v�Z
void Particle::CalcDensity(std::vector<Particle*>& particles)
{
    float h2 = h * h;                                       // �e�����a��2��

    float sum = 0.0f;

    for (auto& other : particles)
    {
        if (other == this) continue;                        // �������g�̓X�L�b�v

        Vector3 diff = other->position - this->position;    // �����̌v�Z
        float r2 = diff.LengthSquared();                    // �����̓��

        // �e���͈͓��̂��̂����v�Z
        if (r2 < h2)
        {
            float c = h2 - r2;
            sum += std::pow(c, 3);
        }
    }

    this->density = sum * densityCoef;                      // ���x�̌v�Z
}

// ���q�̈��͌v�Z
void Particle::CalcPressure(std::vector<Particle*>& particles)
{
    for (int i = 0; i < particles.size(); i++) // �e���q�̈��͂��v�Z
    {
        particles[i]->pressure = pressureStiffness * (particles[i]->density - restDensity);
    }
}

// ���͍����v�Z
void Particle::CalcForce(std::vector<Particle*>& particles)
{
    // ������
    force = Vector3::Zero;
    float h2 = h * h;

    // �e���q���v�Z
    for (auto& other : particles)
    {
        if (other == this) continue;                        // �������g�𖳎�

        Vector3 diff = this->position - other->position;    // �������v�Z
        float r2 = diff.LengthSquared();

        if (r2 < h2)
        {
            float r = std::sqrt(r2);
            if (r > 0.0001f)
            {
                // ===== ���� =====
                float c = h - r;
                float pressureCoef = -45.0f * particleMass / (DirectX::XM_PI * std::pow(h, 6));
                float pressureTerm = (this->pressure + other->pressure) / (2.0f * other->density);
                Vector3 gradW = pressureCoef * (c * c) * (diff / r);
                force += -pressureTerm * gradW;

                // ===== �S�� =====
                float viscosityCoef = 45.0f * viscosity / (DirectX::XM_PI * std::pow(h, 6));
                Vector3 velDiff = other->velocity - this->velocity;
                float laplacianW = viscosityCoef * (h - r);
                Vector3 viscousForce = particleMass * velDiff / other->density * laplacianW;
                force += viscousForce;
            }
        }
    }

    // ===== �d�� =====
    Vector3 gravity = Vector3(0.0f, -9.8f, 0.0f);
    force += density * gravity;
}

// �����蔻��(���E����)
void Particle::ApplyBoundaryForce(const Vector3& minBound, const Vector3& maxBound, float boundaryStiffness)
{
    // �e���Ŕ͈͊O�Ȃ甽���͂�������
    if (position.x < minBound.x)
        force.x += boundaryStiffness * (minBound.x - position.x);
    else if (position.x > maxBound.x)
        force.x += boundaryStiffness * (maxBound.x - position.x);

    if (position.y < minBound.y)
        force.y += boundaryStiffness * (minBound.y - position.y);
    else if (position.y > maxBound.y)
        force.y += boundaryStiffness * (maxBound.y - position.y);

    if (position.z < minBound.z)
        force.z += boundaryStiffness * (minBound.z - position.z);
    else if (position.z > maxBound.z)
        force.z += boundaryStiffness * (maxBound.z - position.z);

    // �g����
    // particle->ApplyBoundaryForce(Vector3(0, 0, 0), Vector3(1, 1, 1), 1000.0f);
}



