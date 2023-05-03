#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "BaseLight.h"

class SAUCA_API DirectionalLight : public BaseLight
{
public:
	DirectionalLight(Renderer* renderer);
};

#endif