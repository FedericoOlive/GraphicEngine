#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>
#include "Exports.h"

struct SAUCA_API Plane
{
	glm::vec3 normal = { 0.f, 1.f, 0.f };
	float distance = 0.0f;

	Plane();
	Plane(const glm::vec3& p1, const glm::vec3& norm);
	bool GetSide(glm::vec3 point);
	float GetSignedDistanceToPlane(const glm::vec3& point) const;
	void SetPositionAndNormal(glm::vec3 point, glm::vec3 normal);
	static glm::vec3 FindIntersectionPoint2(const Plane& plane1, const Plane& plane2, const Plane& plane3);
	static glm::vec3 FindIntersectionPoint(const Plane& plane1, const Plane& plane2, const Plane& plane3);
};

#endif