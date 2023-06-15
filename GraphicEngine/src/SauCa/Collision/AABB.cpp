#include "AABB.h"

AABB::AABB()
{
	Update();
}

void AABB::Update()
{
	min = glm::vec3(std::numeric_limits<float>::max());
	max = -glm::vec3(std::numeric_limits<float>::max());
}