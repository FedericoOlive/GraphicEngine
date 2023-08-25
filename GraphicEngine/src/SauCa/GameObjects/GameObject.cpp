#include "GameObject.h"
#include "Renderer.h"
#include "Render/BinarySpacePartitioning.h"
#include "Render/Camera.h"
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
	while (!components.empty())
	{
		auto iter = components.begin();

		if ((*iter) != nullptr)
		{
			delete (*iter);
			(*iter) = nullptr;
		}
		components.pop_front();
	}

	while (!transform->childrens.empty())
	{
		auto iter = transform->childrens.begin();
		if ((*iter)->gameObject != nullptr)
		{
			delete (*iter)->gameObject;
			(*iter)->gameObject = nullptr;
		}
		transform->childrens.pop_front();
	}

	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}
}

void GameObject::Draw(Camera* camera, Frustum* frustum)
{
	if (isActive && isActiveInHierarchy)
	{
		if (transform->aabbGlobal->IsOnFrustum(*frustum, transform->aabbGlobal))
		{
			if (transform->aabbLocal->IsOnFrustum(*frustum, transform->aabbLocal))
			{
				if (alwaysVisible || BinarySpacePartitioning::IsDraweable(transform))
				{
					for (auto iterComponent = components.begin(); iterComponent != components.end(); ++iterComponent)
					{
						bool isRenderizable = (*iterComponent)->IsRenderizable();
						bool isEnable = (*iterComponent)->isEnable;

						if (isRenderizable && isEnable)
							(*iterComponent)->Draw(camera);
					}
				}
			}

			for (auto iter = transform->childrens.begin(); iter != transform->childrens.end(); ++iter)
			{
				(*iter)->gameObject->Draw(camera, frustum);
			}
		}
	}
}

bool GameObject::IsActive()
{
	return isActive;
}

bool GameObject::IsActiveInHierarch()
{
	return isActiveInHierarchy;
}

void GameObject::SetActive(bool isActive)
{
	this->isActive = isActive;
	SetActiveInHierarch(isActive);
}

void GameObject::SetActiveInHierarch(bool isActiveInHierarchy)
{
	this->isActiveInHierarchy = isActiveInHierarchy;
	
	if (isActiveInHierarchy)
	{
		if(isActive)
			for (auto iter = transform->childrens.begin(); iter != transform->childrens.end(); ++iter)
				(*iter)->gameObject->SetActiveInHierarch(true);
	}
	else
	{
		for (auto iter = transform->childrens.begin(); iter != transform->childrens.end(); ++iter)		
			(*iter)->gameObject->SetActiveInHierarch(false);		
	}
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

	components.remove(component);
	components.push_back(component);
}