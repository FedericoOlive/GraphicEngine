#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <vector>

#include "GameObjects/Component.h"

template<typename... Args>
class Event
{
private:
    std::vector<std::function<void(Args...)>> listeners_;

public:
    void AddListener(const std::function<void(Args...)>& func)
    {
        listeners_.push_back(func);
    }

    void Invoke(Args... args)
    {
        for (auto listener : listeners_)
        {
            listener(args...);
        }
    }
};

#endif