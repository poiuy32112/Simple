#pragma once
#include "Event.h"
#include <string>
#include <functional>

class Window {
public:
    virtual ~Window() = default;

    virtual void OnUpdate() = 0;
    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    // 使用更清晰的类型别名定义事件回调
    using EventCallbackFn = std::function<void(Event&)>;
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    static Window* Create(const std::string& title = "游戏引擎", 
                         unsigned int width = 1280, 
                         unsigned int height = 720);
}; 