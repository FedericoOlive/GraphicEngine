#ifndef MATERIAL_H
#define MATERIAL_H

#include "Exports.h"
#include "Shaders/Shader.h"
#include <glm/glm/vec3.hpp>

class SAUCA_API Material
{
public:
	glm::vec3 colorTint;
	Shader* shader;
	bool hasTexture;
	
	Material(Shader* newShader, bool hasTexture);
	~Material();
};

#endif