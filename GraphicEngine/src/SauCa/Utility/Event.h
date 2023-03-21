#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <vector>

#include "GameObjects/Component.h"

class Event
{
private:
    std::vector<std::function<void()>> listeners_;

public:
	void AddListener(std::function<void()> func);
	void Invoke();
};

#endif