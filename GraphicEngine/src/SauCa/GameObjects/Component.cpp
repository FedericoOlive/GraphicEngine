#include "Component.h"
#include "BaseGame.h"
#include <functional>

Component::Component(bool isRenderizable)
{
	this->isRenderizable = isRenderizable;
	std::function<void()> update = [this] { Update(); };
	std::function<void()> input = [this] { Input(); };
	BaseGame::OnUpdateEvent.AddListener(update);
	BaseGame::OnInputEvent.AddListener(input);
}

void Component::Update()
{
	if (gameobject != nullptr)
	{
		//std::cout << "Update de " << gameobject->name << "\n";
		
	}
}

void Component::Input()
{
	
}

void Component::OnAsigned()
{

}
