#include "Renderer.h"
#include "Camera.h"
#include "App.h"
#include "input.h"
#include "Game.h"

using namespace DirectX::SimpleMath;
using namespace std;


//=======================================
//初期化処理
//=======================================
void Camera::Init()
{
	m_Position	= Vector3(0.0f, 5.0f, -50.0f);
	m_Target	= Vector3(0.0f, 0.0f, 0.0f);
	m_CameraDirection = 3.14f;
}


//=======================================
//更新処理
//=======================================
void Camera::Update()
{
	m_Position.z++;
}


//=======================================
//描画処理
//=======================================
void Camera::Draw()
{

}


//=======================================
//終了処理
//=======================================
void Camera::Uninit()
{
	
}

//=======================================
//終了処理
//=======================================
void Camera::SetCamera(int mode) {
	//3D
	if (mode == 0) {

		// ビュー変換後列作成
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // 左手系				

		Renderer::SetViewMatrix(&m_ViewMatrix);

		//プロジェクション行列の生成
		constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // 視野角

		float aspectRatio = static_cast<float>(App::GetWidth()) / static_cast<float>(App::GetHeight());	// アスペクト比	
		float nearPlane = 1.0f;       // ニアクリップ
		float farPlane = 1000.0f;      // ファークリップ

		//プロジェクション行列の生成
		Matrix projectionMatrix;
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// 左手系

		Renderer::SetProjectionMatrix(&projectionMatrix);
	}

	//2D
	else if (mode == 1) {
		Vector3 pos = { 0.0f, 0.0f, -10.0f };
		Vector3 tgt = { 0.0f, 0.0f, 1.0f };
		Vector3 up = { 0.0f, 1.0f, 0.0f };
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(pos, tgt, up);
		Renderer::SetViewMatrix(&m_ViewMatrix);

		//プロジェクション行列生成
		float nearPlane = 1.0f;		//ニアクリップ
		float farPlane = 1000.0f;	//ファークリップ
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