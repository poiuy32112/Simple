#include "Core/EventDispatcher.h"
#include "Core/Logger.h"
#include <Windows.h>
#include <iostream>

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

    // 注册事件监听器
    EventDispatcher::Get().AddListener(EventType::WindowResize, OnWindowResize);
    EventDispatcher::Get().AddListener(EventType::KeyPressed, OnKeyPressed);

    // 模拟一些事件
    WindowResizeEvent resizeEvent(1280, 720);
    EventDispatcher::Get().Dispatch(resizeEvent);

    KeyPressedEvent keyEvent(65); // 'A' 键
    EventDispatcher::Get().Dispatch(keyEvent);

    MessageBox(NULL, L"Hello World!", L"我的游戏引擎", MB_OK);

    Logger::Info("游戏引擎关闭");
    std::cin.get();
    return 0;
}