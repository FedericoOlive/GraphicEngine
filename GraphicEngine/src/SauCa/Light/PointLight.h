#pragma once
#include "BaseLight.h"

class PointLight : public BaseLight
{
	float constant;
	float linear;
	float quadratic;
	
	PointLight();
	void OnAsigned() override;
};