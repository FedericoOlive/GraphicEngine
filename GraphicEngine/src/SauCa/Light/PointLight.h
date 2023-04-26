#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "BaseLight.h"

class SAUCA_API PointLight : public BaseLight
{
public:
	float constant;
	float linear;
	float quadratic;
	
	PointLight(Renderer* renderer);
};

#endif