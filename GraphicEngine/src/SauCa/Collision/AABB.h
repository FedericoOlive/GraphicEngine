#ifndef AABB_H
#define AABB_H

#include "Exports.h"
#include <glm/vec3.hpp>

class SAUCA_API AABB
{
public:
	glm::vec3 min = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 max = -glm::vec3(std::numeric_limits<float>::max());

	void Update();
	void UpdateMin(glm::vec3 min);
	void UpdateMax(glm::vec3 max);
};

#endif