#include "Entity.h"

Entity::Entity()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

void Entity::SetColorTint(float r, float g, float b)
{
	colorTint = glm::vec4(r, g, b, 1.0f);
}