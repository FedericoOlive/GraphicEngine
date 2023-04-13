#pragma once
#include "BaseLight.h"

class SAUCA_API DirectionlLight : public BaseLight
{
public:
	DirectionlLight();
	void OnAsigned() override;
};