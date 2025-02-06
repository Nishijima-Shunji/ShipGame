#include <chrono>
#include <thread>
#include "App.h"
#include "Renderer.h"

#include "Game.h"

const auto ClassName = TEXT("2024 framework �ЂȌ^");     //!< �E�B���h�E�N���X��.
const auto WindowName = TEXT("2024 framework �ЂȌ^(�t�B�[���h�`��)");    //!< �E�B���h�E��.

HINSTANCE  App::m_hInst;        // �C���X�^���X�n���h��
HWND       App::m_hWnd;         // �E�B���h�E�n���h��
uint32_t   App::m_Width;        // �E�B���h�E�̉���
uint32_t   App::m_Height;       // �E�B���h�E�̏c��

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
App::App(uint32_t width, uint32_t height)
{
	m_Height = height;
	m_Width = width;

	timeBeginPeriod(1);
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
App::~App()
{
	timeEndPeriod(1);
}

//-----------------------------------------------------------------------------
// ���s
//-----------------------------------------------------------------------------
void App::Run()
{
	if (InitApp())
	{
		MainLoop();
	}

	TermApp();
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
bool App::InitApp()
{
	// �E�B���h�E�̏�����.
	if (!InitWnd())
	{
		return false;
	}

	// ����I��.
	return true;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void App::TermApp()
{
	// �E�B���h�E�̏I������.
	TermWnd();
}

//-----------------------------------------------------------------------------
// �E�B���h�E�̏���������
//-----------------------------------------------------------------------------
bool App::InitWnd()
{
	// �C���X�^���X�n���h�����擾.
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr)
	{
		return false;
	}

	// �E�B���h�E�̐ݒ�.
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	// �E�B���h�E�̓o�^.
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	// �C���X�^���X�n���h���ݒ�.
	m_hInst = hInst;

	// �E�B���h�E�̃T�C�Y��ݒ�.
	RECT rc = {};
	rc.right = static_cast<LONG>(m_Width);
	rc.bottom = static_cast<LONG>(m_Height);

	// �E�B���h�E�T�C�Y�𒲐�.
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// �E�B���h�E�𐶐�.
	m_hWnd = CreateWindowEx(
		0,
		//        WS_EX_TOPMOST,
		ClassName,
		WindowName,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		m_hInst,
		nullptr);

	if (m_hWnd == nullptr)
	{
		return false;
	}

	// �E�B���h�E��\��.
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// �E�B���h�E���X�V.
	UpdateWindow(m_hWnd);

	// �E�B���h�E�Ƀt�H�[�J�X��ݒ�.
	SetFocus(m_hWnd);

	// ����I��.
	return true;
}

//-----------------------------------------------------------------------------
// �E�B���h�E�̏I������
//-----------------------------------------------------------------------------
void App::TermWnd()
{
	// �E�B���h�E�̓o�^������.
	if (m_hInst != nullptr)
	{
		UnregisterClass(ClassName, m_hInst);
	}

	m_hInst = nullptr;
	m_hWnd = nullptr;
}

//-----------------------------------------------------------------------------
// ���C�����[�v
//-----------------------------------------------------------------------------
void App::MainLoop()
{
	MSG msg = {};

	Game::Init();

	// FPS�v���p�ϐ�
	int fpsCounter = 0;
	long long oldTick = GetTickCount64(); // �O��v�����̎���
	long long nowTick = oldTick; // ����v�����̎���

	// FPS�Œ�p�ϐ�
	LARGE_INTEGER liWork; // work�����ϐ��͍�Ɨp�ϐ�
	long long frequency;// �ǂꂭ�炢�ׂ������Ԃ��J�E���g�ł��邩
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;
	// ���ԁi�P�ʁF�J�E���g�j�擾
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;// �O��v�����̎���
	long long nowCount = oldCount;// ����v�����̎���


	// �Q�[�����[�v
	while (1)
	{
		// �V���Ƀ��b�Z�[�W�������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// �uWM_QUIT�v���b�Z�[�W���󂯎�����烋�[�v�𔲂���
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			QueryPerformanceCounter(&liWork);// ���ݎ��Ԃ��擾
			nowCount = liWork.QuadPart;
			// 1/60�b���o�߂������H
			if (nowCount >= oldCount + frequency / 60) {



				// �Q�[���������s

				// �X�V
				Game::Update();

				Game::Draw();


				fpsCounter++; // �Q�[�����������s������{�P����
				oldCount = nowCount;
			}


		}
	}

	// �e�X�g�v���[���I������
	Game::Uninit();

	// �`��I������
	Renderer::Uninit();
}

//-----------------------------------------------------------------------------
// �E�B���h�E�v���V�[�W��
//-----------------------------------------------------------------------------
LRESULT CALLBACK App::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
	{
		PostQuitMessage(0);// �uWM_QUIT�v���b�Z�[�W�𑗂�@���@�A�v���I��
	}
	break;

	case WM_CLOSE:  // �ux�v�{�^���������ꂽ��
	{
		int res = MessageBoxA(NULL, "�I�����܂����H", "�m�F", MB_OKCANCEL);
		if (res == IDOK) {
			DestroyWindow(hWnd);  // �uWM_DESTROY�v���b�Z�[�W�𑗂�
		}
	}
	break;

	case WM_KEYDOWN: //�L�[���͂����������b�Z�[�W
	{
		if (LOWORD(wParam) == VK_ESCAPE) { //���͂��ꂽ�L�[��ESCAPE�Ȃ�
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);//�uWM_CLOSE�v�𑗂�
		}
	}
	break;

	default:
	{   // �󂯎�������b�Z�[�W�ɑ΂��ăf�t�H���g�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	}

	return 0;
}
