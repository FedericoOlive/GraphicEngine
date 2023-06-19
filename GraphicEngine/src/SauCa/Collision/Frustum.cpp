#include "Frustum.h"
#include <glm/ext/scalar_constants.hpp>

void Frustum::Update(float fov, float aspect, float far, float near, glm::vec3 camPos, glm::vec3 camForward,
	glm::vec3 camRight, glm::vec3 camUp)
{
	float halfheight = far * (glm::tan((fov * .5f) * glm::pi<float>() / 180.f));
	float halfWidth = halfheight * aspect;
	glm::vec3 frontFar = far * camForward;

	nearFace.SetPositionAndNormal(camPos + near * camForward, camForward);
	farFace.SetPositionAndNormal(camPos + frontFar, -camForward);
	rightFace.SetPositionAndNormal(camPos, glm::cross(camUp, frontFar + camRight * halfWidth));
	leftFace.SetPositionAndNormal(camPos, glm::cross(frontFar - camRight * halfWidth, camUp));
	topFace.SetPositionAndNormal(camPos, glm::cross(camRight, frontFar - camUp * halfheight));
	bottomFace.SetPositionAndNormal(camPos, glm::cross(frontFar + camUp * halfheight, camRight));
}