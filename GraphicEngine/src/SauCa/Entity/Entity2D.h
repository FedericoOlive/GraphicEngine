#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Exports.h"
#include "Entity.h"
#include "Entity2D/Material.h"

class SAUCA_API Entity2D : public Entity
{
public:
	float* vertices;
	int sizeVertices;
	
	int* indices;
	int sizeIndices;
	
	Entity2D();
};

#endif