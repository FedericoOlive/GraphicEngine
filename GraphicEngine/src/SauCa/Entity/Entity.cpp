#include "Entity.h"

#include "CollisionManager.h"

Entity::Entity() : Component()
{
	isRenderizable = true;

	VAO = 0;
	VBO = 0;
	EBO = 0;
	alpha = 1.0f;
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