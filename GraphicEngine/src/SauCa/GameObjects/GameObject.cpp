#include "GameObject.h"
#include "Renderer.h"

unsigned int GameObject::id = 0;

GameObject::GameObject(std::string name)
{
	this->name = name;
	id++;
	if (name.empty())
		this->name = "GameObject " + std::to_string(id);
	transform = new Transform(this);
}

GameObject::~GameObject()
{
	for (auto iter = components.begin(); iter != components.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete* iter;
			(*iter) = nullptr;
		}
	}

	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}
	
	components.clear();
}

template <typename T> T* GameObject::GetComponent()
{
	for (Component* component : components)
	{
		if (T* t = dynamic_cast<T*>(component))
		{
			return t;
		}
	}
	
	return nullptr;
}

template <typename T> void GameObject::RemoveComponent()
{
	for (auto iter = components.begin(); iter != components.end(); ++iter)
	{
		if (dynamic_cast<T*>(*iter))
		{
			delete*iter;
			components.erase(iter);
			break;
		}
	}
}

void GameObject::AddComponent(Component* component)
{
	component->gameobject = this;
	component->transform = transform;
	component->OnAsigned();

	components.push_back(component);
	if (component->isRenderizable)
	{
		Renderer::AddToRenderList(component);
	}
}