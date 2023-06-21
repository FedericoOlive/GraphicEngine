#include "Component.h"
#include "BaseGame.h"
#include <functional>

Component::Component(bool isRenderizable)
{
	this->isRenderizable = isRenderizable;
	//std::function<void(double, double)> onMouseMove = [this](double x, double y) { OnMouseMove(x, y); };
	std::function<void(double)> update = [this](double deltaTime){ Update(deltaTime); };
	std::function<void()> input = [this] { Input(); };
	BaseGame::OnUpdateEvent.AddListener(update);
	BaseGame::OnInputEvent.AddListener(input);
}

void Component::Update(double deltaTime)
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
