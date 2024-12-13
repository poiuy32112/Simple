#include "WindowsWindow.h"
#include "Core/Logger.h"
#include <windowsx.h>

static WCHAR* ConvertToWChar(const std::string& str) {
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    WCHAR* wstr = new WCHAR[size];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, size);
    return wstr;
}

Window* Window::Create(const std::string& title, unsigned int width, unsigned int height) {
    return new WindowsWindow(title, width, height);
}

WindowsWindow::WindowsWindow(const std::string& title, unsigned int width, unsigned int height) {
    Init(title, width, height);
}

WindowsWindow::~WindowsWindow() {
    Shutdown();
}

void WindowsWindow::Init(const std::string& title, unsigned int width, unsigned int height) {
    m_Data.Title = title;
    m_Data.Width = width;
    m_Data.Height = height;
    m_Data.EventCallback = nullptr;

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"GameEngineWindow";
    wc.style = CS_OWNDC;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassEx(&wc))
    {
        Logger::Error("Window class registration failed");
        return;
    }

    WCHAR* wtitle = ConvertToWChar(title);
    
    RECT rect = { 0, 0, (LONG)width, (LONG)height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m_Window = CreateWindowEx(
        0,
        L"GameEngineWindow",
        wtitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    delete[] wtitle;

    if (m_Window == nullptr) {
        Logger::Error("窗口创建失败");
        return;
    }

    SetWindowLongPtr(m_Window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    m_HDC = GetDC(m_Window);

    ShowWindow(m_Window, SW_SHOW);
    UpdateWindow(m_Window);
    Logger::Info("窗口创建成功");
}

void WindowsWindow::Shutdown() {
    if (m_Window) {
        DestroyWindow(m_Window);
        m_Window = nullptr;
    }
}

void WindowsWindow::OnUpdate() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void WindowsWindow::SetVSync(bool enabled) {
    m_Data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const {
    return m_Data.VSync;
}

LRESULT CALLBACK WindowsWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (msg) {
        case WM_SIZE: {
            if (window && window->m_Data.EventCallback) {
                window->m_Data.Width = LOWORD(lParam);
                window->m_Data.Height = HIWORD(lParam);

                WindowResizeEvent event(LOWORD(lParam), HIWORD(lParam));
                window->m_Data.EventCallback(event);
            }
            return 0;
        }
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
} 