#include "Entity.h"

Entity::Entity()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
	modelMatrix = glm::mat4(1.0f);
	translateMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
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
	translateMatrix = glm::mat4(1.0f);
	translateMatrix = glm::translate(translateMatrix, translate);
	SetModelMatrix();
}

void Entity::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
	scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, scale);
	SetModelMatrix();
}

void Entity::SetRotation(float x, float y, float z, bool time)
{
	rotation = glm::vec3(x, y, z);
	rotationMatrix = glm::mat4(1.0f);
	if (!time) 
	{
		rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else 
	{
		rotationMatrix = glm::rotate(rotationMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	SetModelMatrix();
}

void Entity::SetModelMatrix() 
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
}