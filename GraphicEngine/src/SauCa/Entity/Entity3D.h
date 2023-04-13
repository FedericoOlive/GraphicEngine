#pragma once
#include "GameObjects/Component.h"
#include "Entity.h"

class SAUCA_API Entity3D : public Entity
{
private:
protected:
	float* vertices;
	int sizeVertices;

	int* indices;
	int sizeIndices;
public:
	Entity3D();
};