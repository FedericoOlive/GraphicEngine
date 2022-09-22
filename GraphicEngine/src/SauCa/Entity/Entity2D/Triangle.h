#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
class SAUCA_API Triangle : public Shape
{
public:
	Triangle(Renderer* renderer);
	~Triangle();
	void Draw();
};

#endif