#pragma once
#include "Event.h"
#include <functional>
#include <unordered_map>
#include <vector>

class EventDispatcher
{
public:
    using EventCallback = std::function<void(Event&)>;

    static EventDispatcher& Get()
    {
        static EventDispatcher instance;
        return instance;
    }

    // 添加事件监听器
    void AddListener(EventType type, const EventCallback& callback)
    {
        m_Listeners[type].push_back(callback);
    }

    // 分发事件
    void Dispatch(Event& event)
    {
        EventType type = event.GetType();
        if (m_Listeners.find(type) != m_Listeners.end())
        {
            for (auto& callback : m_Listeners[type])
            {
                callback(event);
                if (event.handled)
                    break;
            }
        }
    }

private:
    EventDispatcher() = default;
    std::unordered_map<EventType, std::vector<EventCallback>> m_Listeners;
};