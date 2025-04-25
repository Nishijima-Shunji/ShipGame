#include "Particle.h"

Particle::Particle(Camera* cam) : Object(cam) {

}

Particle::~Particle() {

}

void Particle::Init() {
    // 頂点1個だけ定義（パーティクルは1点として描画）
    m_Vertex.position = Vector3(0, 0, 0);
    m_Vertex.color = Color(1, 1, 1, 1);  // 白
    m_Vertex.uv = Vector2(0, 0);
    m_Vertex.normal = Vector3(0, 1, 0);

    std::vector<VERTEX_3D> verts = { m_Vertex };
    m_VertexBuffer.Create(verts);

    // シェーダ
    m_Shader.Create("shader/unlitVS.hlsl", "shader/unlitPS.hlsl");

    // テクスチャ（任意）
    m_Texture.Load("assets/texture/particle.png");

    // マテリアル
    m_Material = std::make_unique<Material>();
    MATERIAL mtrl;
    mtrl.Diffuse = Color(1, 1, 1, 1);
    mtrl.Shiness = 1;
    mtrl.TextureEnable = true;
    m_Material->Create(mtrl);
}

void Particle::Update() {
    

    float dt = 0.016f; // 時間ステップ（秒）

    // 加速度 a = f / ρ
    Vector3 acceleration = force / density;

    // 速度更新
    velocity += acceleration * dt;

    // 位置更新
    position += velocity * dt;
}

void Particle::Draw() {

}

void Particle::Uninit() {

}

//粒子の密度計算
void Particle::CalcDensity(std::vector<Particle*>& particles)
{
    float h2 = h * h;                                       // 影響半径の2乗

    float sum = 0.0f;

    for (auto& other : particles)
    {
        if (other == this) continue;                        // 自分自身はスキップ

        Vector3 diff = other->position - this->position;    // 距離の計算
        float r2 = diff.LengthSquared();                    // 距離の二乗

        // 影響範囲内のものだけ計算
        if (r2 < h2)
        {
            float c = h2 - r2;
            sum += std::pow(c, 3);
        }
    }

    this->density = sum * densityCoef;                      // 密度の計算
}

// 粒子の圧力計算
void Particle::CalcPressure(std::vector<Particle*>& particles)
{
    for (int i = 0; i < particles.size(); i++) // 各粒子の圧力を計算
    {
        particles[i]->pressure = pressureStiffness * (particles[i]->density - restDensity);
    }
}

// 圧力項を計算
void Particle::CalcForce(std::vector<Particle*>& particles)
{
    // 初期化
    force = Vector3::Zero;
    float h2 = h * h;

    // 各粒子を計算
    for (auto& other : particles)
    {
        if (other == this) continue;                        // 自分自身を無視

        Vector3 diff = this->position - other->position;    // 距離を計算
        float r2 = diff.LengthSquared();

        if (r2 < h2)
        {
            float r = std::sqrt(r2);
            if (r > 0.0001f)
            {
                // ===== 圧力 =====
                float c = h - r;
                float pressureCoef = -45.0f * particleMass / (DirectX::XM_PI * std::pow(h, 6));
                float pressureTerm = (this->pressure + other->pressure) / (2.0f * other->density);
                Vector3 gradW = pressureCoef * (c * c) * (diff / r);
                force += -pressureTerm * gradW;

                // ===== 粘性 =====
                float viscosityCoef = 45.0f * viscosity / (DirectX::XM_PI * std::pow(h, 6));
                Vector3 velDiff = other->velocity - this->velocity;
                float laplacianW = viscosityCoef * (h - r);
                Vector3 viscousForce = particleMass * velDiff / other->density * laplacianW;
                force += viscousForce;
            }
        }
    }

    // ===== 重力 =====
    Vector3 gravity = Vector3(0.0f, -9.8f, 0.0f);
    force += density * gravity;
}

// 当たり判定(境界反発)
void Particle::ApplyBoundaryForce(const Vector3& minBound, const Vector3& maxBound, float boundaryStiffness)
{
    // 各軸で範囲外なら反発力を加える
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

    // 使い方
    // particle->ApplyBoundaryForce(Vector3(0, 0, 0), Vector3(1, 1, 1), 1000.0f);
}



