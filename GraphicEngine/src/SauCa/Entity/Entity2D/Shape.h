#ifndef SHAPE_H
#define SHAPE_H

#include "Entity/Entity2D.h"

class SAUCA_API Shape : public Entity2D
{

public:
	Shape();
	int sizeVertices;
	int sizeIndices;
	
	float* vertices;
	int* indices;
protected:
	
};
#endif
