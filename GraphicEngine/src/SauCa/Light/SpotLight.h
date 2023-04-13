#pragma once
#include "BaseLight.h"

class SAUCA_API SpotLight : public BaseLight
{
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	
	SpotLight();
	void OnAsigned() override;
};