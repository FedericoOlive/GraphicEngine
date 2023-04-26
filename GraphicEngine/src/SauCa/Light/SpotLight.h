#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
#include "BaseLight.h"

class SAUCA_API SpotLight : public BaseLight
{
public:
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	
	SpotLight(Renderer* renderer);
};

#endif