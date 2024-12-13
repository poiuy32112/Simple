#include "Core/EventDispatcher.h"
#include "Core/Logger.h"
#include <Windows.h>
#include <iostream>

void OnWindowResize(Event& e)
{
    WindowResizeEvent& resizeEvent = static_cast<WindowResizeEvent&>(e);
    Logger::Info("���ڴ�С�ı�: " + std::to_string(resizeEvent.GetWidth()) +
        "x" + std::to_string(resizeEvent.GetHeight()));
}

void OnKeyPressed(Event& e)
{
    KeyPressedEvent& keyEvent = static_cast<KeyPressedEvent&>(e);
    Logger::Info("��������: " + std::to_string(keyEvent.GetKeyCode()));
}

int main()
{
    Logger::Init();
    Logger::Info("��Ϸ��������");

    // ע���¼�������
    EventDispatcher::Get().AddListener(EventType::WindowResize, OnWindowResize);
    EventDispatcher::Get().AddListener(EventType::KeyPressed, OnKeyPressed);

    // ģ��һЩ�¼�
    WindowResizeEvent resizeEvent(1280, 720);
    EventDispatcher::Get().Dispatch(resizeEvent);

    KeyPressedEvent keyEvent(65); // 'A' ��
    EventDispatcher::Get().Dispatch(keyEvent);

    MessageBox(NULL, L"Hello World!", L"�ҵ���Ϸ����", MB_OK);

    Logger::Info("��Ϸ����ر�");
    std::cin.get();
    return 0;
}