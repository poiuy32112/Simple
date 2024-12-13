#pragma once
#include "Core/Window.h"
#include <Windows.h>

class WindowsWindow : public Window {
public:
    WindowsWindow(const std::string& title, unsigned int width, unsigned int height);
    virtual ~WindowsWindow();

    void OnUpdate() override;
    unsigned int GetWidth() const override { return m_Data.Width; }
    unsigned int GetHeight() const override { return m_Data.Height; }

    void SetEventCallback(const std::function<void(Event&)>& callback) override
    { m_Data.EventCallback = callback; }
    
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

private:
    void Init(const std::string& title, unsigned int width, unsigned int height);
    void Shutdown();

    HWND m_Window;
    HDC m_HDC;

    struct WindowData {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}; 