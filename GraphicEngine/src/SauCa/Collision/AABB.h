#ifndef AABB_H
#define AABB_H

#include "Exports.h"
#include <glm/vec3.hpp>

class SAUCA_API AABB
{
public:
	glm::vec3 min;
	glm::vec3 max;

	AABB();
	void Update();
};

#endif