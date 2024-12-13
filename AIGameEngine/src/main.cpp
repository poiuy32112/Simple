#include "Core/EventDispatcher.h"
#include "Core/Logger.h"
#include "Core/Window.h"
#include <Windows.h>
#include <iostream>
#include <memory>

void OnWindowResize(Event& e)
{
    WindowResizeEvent& resizeEvent = static_cast<WindowResizeEvent&>(e);
    Logger::Info("窗口大小改变: " + std::to_string(resizeEvent.GetWidth()) +
        "x" + std::to_string(resizeEvent.GetHeight()));
}

void OnKeyPressed(Event& e)
{
    KeyPressedEvent& keyEvent = static_cast<KeyPressedEvent&>(e);
    Logger::Info("按键按下: " + std::to_string(keyEvent.GetKeyCode()));
}

int main()
{
    Logger::Init();
    Logger::Info("游戏引擎启动");

    // 创建窗口
    std::unique_ptr<Window> window(Window::Create("我的游戏引擎", 1280, 720));
    if (!window) {
        Logger::Error("窗口创建失败");
        return -1;
    }
    
    // 设置事件回调
    window->SetEventCallback([](Event& e) {
        EventDispatcher::Get().Dispatch(e);
    });

    // 注册事件监听器
    EventDispatcher::Get().AddListener(EventType::WindowResize, OnWindowResize);
    EventDispatcher::Get().AddListener(EventType::KeyPressed, OnKeyPressed);

    // 主循环
    bool running = true;
    MSG msg = {};
    while (running) 
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (running)
        {
            window->OnUpdate();
        }
    }

    Logger::Info("游戏引擎关闭");
    return 0;
}