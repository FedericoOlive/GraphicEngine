#pragma once
#include "Entity/Entity2D/Shape.h"

class SAUCA_API Quad : public Shape
{
public:
	Quad(Renderer* renderer);
	~Quad();
};