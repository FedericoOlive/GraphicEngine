#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "BaseLight.h"

class SAUCA_API PointLight : public BaseLight
{
	float constant;
	float linear;
	float quadratic;
	
	PointLight();
	void OnAsigned() override;
};

#endif