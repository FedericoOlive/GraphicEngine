#include "Material.h"

Material::Material(Shader* newShader, bool hasTexture)
{
	shader = newShader;
	colorTint = glm::vec3(1, 1, 1);
	this->hasTexture = hasTexture;
}

Material::~Material()
{
	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
}