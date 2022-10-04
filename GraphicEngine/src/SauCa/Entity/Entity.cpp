#include "Entity.h"

Entity::Entity()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
	transform = glm::mat4(1.0f);
	translate = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

void Entity::SetColorTint(float r, float g, float b)
{
	colorTint = glm::vec4(r, g, b, 1.0f);
}

void Entity::SetPosition(float x, float y, float z)
{
	translate = glm::vec3(x, y, z);
}

void Entity::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
}

void Entity::SetRotation(float x, float y, float z)
{
	rotation = glm::vec3(x, y, z);
}