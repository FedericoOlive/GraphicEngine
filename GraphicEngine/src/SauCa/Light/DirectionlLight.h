#pragma once
#include "BaseLight.h"

class DirectionlLight : public BaseLight
{
public:
	DirectionlLight();
	void OnAsigned() override;
};