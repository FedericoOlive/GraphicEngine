#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "GameObjects/Component.h"
#include "glm/glm/gtc/type_ptr.hpp"

class SAUCA_API BaseLight : public Component
{
	public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 lightColor;
	BaseLight();
};

#endif