#pragma once
#include "BaseLight.h"

class SAUCA_API PointLight : public BaseLight
{
	float constant;
	float linear;
	float quadratic;
	
	PointLight();
	void OnAsigned() override;
};