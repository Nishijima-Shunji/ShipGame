#pragma once

#include    <Windows.h>
#include    <cstdint>

//-----------------------------------------------------------------------------
// App�N���X
//-----------------------------------------------------------------------------
class App
{
public:
    App(uint32_t width, uint32_t height);
    ~App();
    void Run();

    // �����擾
    static uint32_t GetWidth() {
        return m_Width;
    }

    // �������擾
    static uint32_t GetHeight() {
        return m_Height;
    }

    // �E�C���h�E�n���h����Ԃ�
    static HWND GetWindow() {
        return m_hWnd;
    }

private:
    static HINSTANCE   m_hInst;        // �C���X�^���X�n���h��
    static HWND        m_hWnd;         // �E�B���h�E�n���h��
    static uint32_t    m_Width;        // �E�B���h�E�̉���
    static uint32_t    m_Height;       // �E�B���h�E�̏c��

    static bool InitApp();
    static void TermApp();
    static bool InitWnd();
    static void TermWnd();
    static void MainLoop();

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};