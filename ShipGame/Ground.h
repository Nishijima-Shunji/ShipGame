#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Object.h"

class Ground : public Object
{
	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	IndexBuffer	 m_IndexBuffer; // �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // ���_�o�b�t�@

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	//Shader m_Shader; // �V�F�[�_�[
	Texture m_Texture;	//�e�N�X�`��
	std::unique_ptr<Material> m_Materiale;	//�}�e���A��

	int m_SizeX;	//���T�C�Y
	int m_SizeZ;	//�c�T�C�Y
	std::vector<VERTEX_3D> m_Vertices;	//���_���

	//=====================================
	float currentTime = 0.0f;

	struct TimerBufferType {
		float Timer;       // �O���[�o���^�C�}�[
		float Padding[3];  // �p�f�B���O��ǉ��iDirectX�ł�16�o�C�g�P�ʁj
	};


public:
	Ground(Camera* cam);	//�R���X�g���N�^
	~Ground();				//�f�X�g���N�^

	void Init();
	void Draw();
	void Update();
	void Uninit();

	//���_�����擾
	std::vector<VERTEX_3D> GetVertices();
};

