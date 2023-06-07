#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "GameObjects/Component.h"
#include "glm/gtc/type_ptr.hpp"
class Renderer;

class SAUCA_API BaseLight : public Component
{
protected:
	Renderer* renderer;
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 lightColor;

	float powerAmbient;
	float powerDiffuse;
	float powerSpecular;
	
	BaseLight(Renderer* renderer);
	void OnAsigned() override;
};

#endif