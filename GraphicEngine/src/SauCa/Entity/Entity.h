#ifndef ENTITY_H
#define ENTITY_H

#include "Exports.h"
#include "Renderer.h"

class SAUCA_API Entity
{
protected:
	Renderer* renderer;
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glm::vec3 translate;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 transform;
	glm::vec4 colorTint;
	Entity();
	void SetColorTint(float r, float g, float b);
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);
};

#endif