#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "BaseLight.h"

class SAUCA_API DirectionlLight : public BaseLight
{
public:
	DirectionlLight();
	void OnAsigned() override;	
};

#endif