#include "Renderer.h"
#include "Camera.h"
#include "App.h"
#include "input.h"
#include "Game.h"

using namespace DirectX::SimpleMath;
using namespace std;


//=======================================
//����������
//=======================================
void Camera::Init()
{
	m_Position	= Vector3(0.0f, 5.0f, -50.0f);
	m_Target	= Vector3(0.0f, 0.0f, 0.0f);
	m_CameraDirection = 3.14f;
}


//=======================================
//�X�V����
//=======================================
void Camera::Update()
{
	m_Position.z++;
}


//=======================================
//�`�揈��
//=======================================
void Camera::Draw()
{

}


//=======================================
//�I������
//=======================================
void Camera::Uninit()
{
	
}

//=======================================
//�I������
//=======================================
void Camera::SetCamera(int mode) {
	//3D
	if (mode == 0) {

		// �r���[�ϊ����쐬
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // ����n				

		Renderer::SetViewMatrix(&m_ViewMatrix);

		//�v���W�F�N�V�����s��̐���
		constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // ����p

		float aspectRatio = static_cast<float>(App::GetWidth()) / static_cast<float>(App::GetHeight());	// �A�X�y�N�g��	
		float nearPlane = 1.0f;       // �j�A�N���b�v
		float farPlane = 1000.0f;      // �t�@�[�N���b�v

		//�v���W�F�N�V�����s��̐���
		Matrix projectionMatrix;
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// ����n

		Renderer::SetProjectionMatrix(&projectionMatrix);
	}

	//2D
	else if (mode == 1) {
		Vector3 pos = { 0.0f, 0.0f, -10.0f };
		Vector3 tgt = { 0.0f, 0.0f, 1.0f };
		Vector3 up = { 0.0f, 1.0f, 0.0f };
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(pos, tgt, up);
		Renderer::SetViewMatrix(&m_ViewMatrix);

		//�v���W�F�N�V�����s�񐶐�
		float nearPlane = 1.0f;		//�j�A�N���b�v
		float farPlane = 1000.0f;	//�t�@�[�N���b�v
		Matrix projectionMatrix = DirectX::XMMatrixOrthographicLH(static_cast<float>(App::GetWidth()), static_cast<float>(App::GetHeight()), nearPlane, farPlane);
		projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);
		Renderer::SetProjectionMatrix(&projectionMatrix);
	}
}

int Camera::GetCameraState() {
	return cameraState;
}

void Camera::SetCameraState(int state) {
	cameraState = state;
}