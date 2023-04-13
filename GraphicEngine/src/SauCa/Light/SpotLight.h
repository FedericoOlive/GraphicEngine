#pragma once
#include "BaseLight.h"

class SpotLight : public BaseLight
{
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	
	SpotLight();
	void OnAsigned() override;
};