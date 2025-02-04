#include "App.h"

bool DX11App::Initialize(HINSTANCE hInstance) {
    if (!InitWindow(hInstance)) return false;
    if (!InitDirect3D()) return false;
    return true;
}

bool DX11App::InitWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"DX11ShipGame", NULL };
    RegisterClassEx(&wc);
    hWnd = CreateWindow(wc.lpszClassName, L"DirectX 11 Ship Game", WS_OVERLAPPEDWINDOW, 100, 100, width, height, NULL, NULL, wc.hInstance, NULL);
    if (!hWnd) return false;
    ShowWindow(hWnd, SW_SHOW);
    return true;
}

bool DX11App::InitDirect3D() {
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION,
        &scd, &swapChain, &device, NULL, &deviceContext);
    if (FAILED(hr)) return false;

    ComPtr<ID3D11Texture2D> backBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
    device->CreateRenderTargetView(backBuffer.Get(), NULL, &renderTargetView);

    struct Vertex {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 color;
    };

    // 船を表現する四角形の頂点データ（2D のため Z = 0）
    Vertex vertices[] = {
        { {-0.1f,  0.1f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} }, // 左上
        { { 0.1f,  0.1f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} }, // 右上
        { {-0.1f, -0.1f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} }, // 左下
        { { 0.1f, -0.1f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} }  // 右下
    };

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    HRESULT hr = device->CreateBuffer(&bd, &initData, &vertexBuffer);
    if (FAILED(hr)) return false;


    return true;
}

void DX11App::Render() {
    float clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);
    swapChain->Present(1, 0);

}

void DX11App::Run() {
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Render();
    }
}

void DX11App::Cleanup() {
    if (renderTargetView) renderTargetView.Reset();
    if (swapChain) swapChain.Reset();
    if (deviceContext) deviceContext.Reset();
    if (device) device.Reset();
    UnregisterClass(L"DX11ShipGame", GetModuleHandle(NULL));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    DX11App app;
    if (!app.Initialize(hInstance)) return 1;
    app.Run();
    app.Cleanup();
    return 0;
}
