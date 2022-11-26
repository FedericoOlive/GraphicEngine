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
	alpha = 1.0f;
}

void Entity::SetColorTint(float r, float g, float b, float a)
{
	material->colorTint = glm::vec3(r, g, b);
	alpha = a;
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
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else 
	{
		rotationMatrix = glm::rotate(rotationMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	SetModelMatrix();
}

glm::vec3 Entity::GetViewportPosition()
{
	glm::vec3 pos = glm::vec3(translate.x + 1, translate.y + 1, translate.z + 1);
	pos.x = (translate.x + 1) * Window::Screen_Width / 2;
	pos.y = (translate.y + 1) * Window::Screen_Height / 2;
	pos.z = (translate.z);

	return translate;
}

void Entity::SetModelMatrix() 
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
}
