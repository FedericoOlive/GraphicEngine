#ifndef MATERIAL_H
#define MATERIAL_H

#include "Exports.h"
#include "Shaders/Shader.h"
#include <glm/vec3.hpp>

class SAUCA_API Material
{
public:
	glm::vec3 colorTint = { 1.0f, 1.0f, 1.0f };;
	Shader* shader;
	bool hasTexture;
	unsigned int albedoTexture;
	glm::vec3 ambient = { 1, 1, 1 };
	glm::vec3 diffuse = { 1, 1, 1 };
	glm::vec3 specular = { 1, 1, 1 };
	float shininess = 32;
	
	Material(Shader* newShader, bool hasTexture);
	~Material();
};

#endif