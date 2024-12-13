#pragma once
#include <string>

// �¼�����ö��
enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// �¼�����
class Event
{
public:
    virtual ~Event() = default;
    virtual EventType GetType() const = 0;
    virtual std::string ToString() const { return "Event"; }

    bool handled = false;
};

// �����¼�
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height)
    {
    }

    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }

    virtual EventType GetType() const override { return EventType::WindowResize; }
    virtual std::string ToString() const override
    {
        return "WindowResizeEvent: " + std::to_string(m_Width) + ", " + std::to_string(m_Height);
    }

private:
    unsigned int m_Width, m_Height;
};

// �����¼�
class KeyEvent : public Event
{
public:
    int GetKeyCode() const { return m_KeyCode; }

protected:
    KeyEvent(int keycode) : m_KeyCode(keycode) {}
    int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keycode) : KeyEvent(keycode) {}

    virtual EventType GetType() const override { return EventType::KeyPressed; }
    virtual std::string ToString() const override
    {
        return "KeyPressedEvent: " + std::to_string(m_KeyCode);
    }
};