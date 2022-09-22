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
	glm::vec4 colorTint;
	Entity();
	void SetColorTint(float r, float g, float b);
};

#endif