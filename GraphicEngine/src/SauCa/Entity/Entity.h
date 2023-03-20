#ifndef ENTITY_H
#define ENTITY_H

#include "Renderer.h"
#include "Entity2D/Material.h"
#include "GameObjects/GameObject.h"

class SAUCA_API Entity : public Component
{
protected:
	Renderer* renderer;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

public:
	float alpha;
	Material* material;

	Entity();
	void SetRenderer(Renderer* renderer);
	
	void SetColorTint(float r, float g, float b, float a);
	void SetColorTint(glm::vec4 tint) { SetColorTint(tint.r, tint.g, tint.b, tint.a); }
};

#endif