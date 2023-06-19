#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Plane.h"

struct SAUCA_API Frustum
{
	Plane topFace;
	Plane bottomFace;
	Plane rightFace;
	Plane leftFace;
	Plane farFace;
	Plane nearFace;
	void Update(float fov, float aspect, float far, float near, glm::vec3 camPos, glm::vec3 camForward,
		glm::vec3 camRight, glm::vec3 camUp);
};

#endif