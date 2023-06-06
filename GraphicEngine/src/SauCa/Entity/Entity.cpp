#include "Entity.h"

#include "CollisionManager.h"

Entity::Entity() : Component()
{
	vertexData = nullptr;
	isRenderizable = true;	
	alpha = 1.0f;
}

Entity::~Entity()
{
	if (vertexData != nullptr)
	{
		delete vertexData;
		vertexData = nullptr;
	}
	if (material != nullptr)
	{
		delete material;
		material = nullptr;
	}
}

void Entity::SetRenderer(Renderer* renderer)
{
	this->renderer = renderer;
}

void Entity::SetColorTint(float r, float g, float b, float a)
{
	material->colorTint = glm::vec3(r, g, b);
	alpha = a;
}