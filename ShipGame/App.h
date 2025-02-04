#pragma once
#include <windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

using namespace Microsoft::WRL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class DX11App {
private:
    bool InitWindow(HINSTANCE hInstance);
    bool InitDirect3D();
    void Render();

    HWND hWnd;
    int width, height;
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> deviceContext;
    ComPtr<IDXGISwapChain> swapChain;
    ComPtr<ID3D11RenderTargetView> renderTargetView;
    ComPtr<ID3D11Buffer> vertexBuffer;
    ComPtr<ID3D11InputLayout> inputLayout;
    ComPtr<ID3D11VertexShader> vertexShader;
    ComPtr<ID3D11PixelShader> pixelShader;


public:
    DX11App() : hWnd(nullptr), width(1280), height(720) {}
    bool Initialize(HINSTANCE hInstance);
    void Run();
    void Cleanup();
};
