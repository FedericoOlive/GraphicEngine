#include "Component.h"
#include "BaseGame.h"
#include <functional>

Component::Component(bool isRenderizable)
{
	this->isRenderizable = isRenderizable;
	std::function<void()> func = [this] { Update(); }; // == std::function<void()> func = std::bind(&Component::Update, this);
	BaseGame::OnUpdateEvent.AddListener(func);
}

void Component::Update()
{
	if (gameobject != nullptr)
		std::cout << "Update de " << gameobject->name << "\n";
}
