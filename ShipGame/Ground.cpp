#include "Ground.h"

#include "stb_image.h"
#include <chrono>
#include <iostream>

using namespace DirectX::SimpleMath;

Ground::Ground(Camera* cam) : Object(cam) {

}


Ground::~Ground() {

}


//=======================================
//����������
//=======================================
void Ground::Init()
{
	m_SizeX = 30;
	m_SizeZ = 30;

	m_Vertices.resize(6 * m_SizeX * m_SizeZ);

	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(6 * m_SizeX * m_SizeZ);
	for (int z = 0; z < m_SizeZ; z++) {
		for (int x = 0; x < m_SizeX; x++) {
			int n = z * m_SizeZ * 6 + x * 6;

			m_Vertices[n + 0].position = Vector3(-0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 1].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 2].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 3].position = Vector3(-0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 4].position = Vector3(0.5 + x - m_SizeX / 2, 0, 0.5 - z + m_SizeZ / 2);
			m_Vertices[n + 5].position = Vector3(0.5 + x - m_SizeX / 2, 0, -0.5 - z + m_SizeZ / 2);

			m_Vertices[n + 0].color = Color(1, 1, 1, 1);
			m_Vertices[n + 1].color = Color(1, 1, 1, 1);
			m_Vertices[n + 2].color = Color(1, 1, 1, 1);
			m_Vertices[n + 3].color = Color(1, 1, 1, 1);
			m_Vertices[n + 4].color = Color(1, 1, 1, 1);
			m_Vertices[n + 5].color = Color(1, 1, 1, 1);

			m_Vertices[n + 0].uv = Vector2(0, 0);
			m_Vertices[n + 1].uv = Vector2(1, 0);
			m_Vertices[n + 2].uv = Vector2(0, 1);
			m_Vertices[n + 3].uv = Vector2(0, 1);
			m_Vertices[n + 4].uv = Vector2(1, 0);
			m_Vertices[n + 5].uv = Vector2(1, 1);

			m_Vertices[n + 0].normal = Vector3(0, 1, 0);
			m_Vertices[n + 1].normal = Vector3(0, 1, 0);
			m_Vertices[n + 2].normal = Vector3(0, 1, 0);
			m_Vertices[n + 3].normal = Vector3(0, 1, 0);
			m_Vertices[n + 4].normal = Vector3(0, 1, 0);
			m_Vertices[n + 5].normal = Vector3(0, 1, 0);

			indices[n + 0] = n + 0;
			indices[n + 1] = n + 1;
			indices[n + 2] = n + 2;
			indices[n + 3] = n + 3;
			indices[n + 4] = n + 4;
			indices[n + 5] = n + 5;
		}
	}
	//�ǂݍ��މ摜�t�@�C���̃p�X
	const char* filename = "assets/texture/terain2.png";

	//�摜�f�[�^���i�[����|�C���^
	unsigned char* imageData = nullptr;
	int width, height, channels;

	//�O���[�X�P�[��(1�`���l��)�ŉ摜��ǂݍ���
	imageData = stbi_load(filename, &width, &height, &channels, 1);
	if (imageData) {
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {
				int picX = x * (float)width / m_SizeX;
				int picY = z * (float)height / m_SizeZ;
				unsigned char pixelValue = imageData[picY * width + picX];
				float h = (float)pixelValue / 15.0f;
				int n = z * m_SizeZ * 6 + x * 6;
				m_Vertices[n + 0].position.y = h;
				if (x != 0)m_Vertices[n - 2].position.y = h;
				if (x != 0)m_Vertices[n - 5].position.y = h;
				if (z != 0)m_Vertices[n - m_SizeX * 6 + 2].position.y = h;
				if (z != 0)m_Vertices[n - m_SizeX * 6 + 3].position.y = h;
				if (x != 0 && z != 0)m_Vertices[n - m_SizeX * 6 - 1].position.y = h;
			}
		}

		//�@���x�N�g�����X�V
		for (int z = 0; z < m_SizeZ; z++) {
			for (int x = 0; x < m_SizeX; x++) {
				int n = z * m_SizeZ * 6 + x * 6;

				//2�̃x�N�g�����v�Z
				Vector3 v1 = m_Vertices[n + 1].position - m_Vertices[n + 0].position;
				Vector3 v2 = m_Vertices[n + 2].position - m_Vertices[n + 0].position;
				Vector3 normal = v1.Cross(v2);	//�O�ς��v�Z
				normal.Normalize();				//���K��
				m_Vertices[n + 0].normal = normal;
				m_Vertices[n + 1].normal = normal;
				m_Vertices[n + 2].normal = normal;

				//2�̃x�N�g�����v�Z
				v1 = m_Vertices[n + 4].position - m_Vertices[n + 3].position;
				v2 = m_Vertices[n + 5].position - m_Vertices[n + 3].position;
				normal = v1.Cross(v2);	//�O�ς��v�Z
				normal.Normalize();				//���K��
				m_Vertices[n + 3].normal = normal;
				m_Vertices[n + 4].normal = normal;
				m_Vertices[n + 5].normal = normal;
			}
		}

		//�����������
		stbi_image_free(imageData);
	}

	// ���_�o�b�t�@����
	m_VertexBuffer.Create(m_Vertices);

	// �C���f�b�N�X�o�b�t�@����
	m_IndexBuffer.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");
	//m_Shader.Create("shader/WaveVS.hlsl", "shader/litTexturePS.hlsl");

	//�e�N�X�`�����[�h
	bool sts = m_Texture.Load("assets/texture/field.jpg");
	// bool sts = m_Texture.Load("assets/texture/water.jpg");
	assert(sts = true);

	//�}�e���A�����擾
	m_Materiale = std::make_unique<Material>();
	MATERIAL mtrl;
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Shiness = 1;
	mtrl.TextureEnable = true;	//�e�N�X�`�����g�����ۂ��̃t���O
	m_Materiale->Create(mtrl);

	//Ground�̈ʒu��傫���𒲐�
	m_Position.y = -0.1f;
	m_Scale.x = 5.0f;
	m_Scale.z = 5.0f;

	//���_����ϊ����Ă���
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	Matrix worldmtx = s * r * t;
	for (int i = 0; i < m_Vertices.size(); i++) {
		m_Vertices[i].position = Vector3::Transform(m_Vertices[i].position, worldmtx);
		m_Vertices[i].normal = Vector3::Transform(m_Vertices[i].normal, worldmtx);
	}
}


//=======================================
//�X�V����
//=======================================
void Ground::Update()
{
	//���ݎ��Ԃ̎擾
	auto now = std::chrono::steady_clock::now();
	static auto start = now;
	currentTime = std::chrono::duration<float>(now - start).count();
}

//=======================================
//�`�揈��
//=======================================
void Ground::Draw()
{
	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll(
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// �g�|���W�[���Z�b�g�i�v���~�e�B�u�^�C�v�j
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();
	m_Materiale->SetGPU();

	//�J�����̐ݒ���w��
	m_Camera->SetCamera(0);

	devicecontext->DrawIndexed(
		6 * m_SizeX * m_SizeZ,		// �`�悷��C���f�b�N�X��
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);

	//============================================
	// �萔�o�b�t�@�̍쐬
	ID3D11Buffer* m_timerBuffer = nullptr;
	ID3D11Device* device = Renderer::GetDevice();
	if (device == nullptr) {
		return; // �������͓K�؂ȃG���[����
	}

	D3D11_BUFFER_DESC timerBufferDesc = {};
	timerBufferDesc.Usage = D3D11_USAGE_DYNAMIC;             // ���I�X�V
	timerBufferDesc.ByteWidth = sizeof(TimerBufferType);     // �o�b�t�@�T�C�Y
	timerBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;  // �萔�o�b�t�@
	timerBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU���珑�����݉\
	timerBufferDesc.MiscFlags = 0;

	HRESULT hr = device->CreateBuffer(&timerBufferDesc, nullptr, &m_timerBuffer);
	if (FAILED(hr)) {
		return; // �G���[������ǉ�
	}

	// ���t���[���^�C�}�[���X�V
	TimerBufferType timerData = {};
	timerData.Timer = currentTime; // ���ݎ��Ԃ�ݒ�

	if (devicecontext == nullptr) {
		return; // �܂��͓K�؂ȃG���[�n���h�����O
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	hr = devicecontext->Map(m_timerBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (SUCCEEDED(hr)) {
		memcpy(mappedResource.pData, &timerData, sizeof(TimerBufferType));
		devicecontext->Unmap(m_timerBuffer, 0);
	}
	else {
	}

	// �萔�o�b�t�@���X���b�g b6 �Ƀo�C���h
	devicecontext->VSSetConstantBuffers(6, 1, &m_timerBuffer); // ���_�V�F�[�_�[�p
	devicecontext->PSSetConstantBuffers(6, 1, &m_timerBuffer); // �s�N�Z���V�F�[�_�[�p

}

//=======================================
//�I������
//=======================================
void Ground::Uninit()
{

}

//=======================================
//�I������
//=======================================
std::vector<VERTEX_3D> Ground::GetVertices() {
	return m_Vertices;
}