#include "AABB.h"

void AABB::BeforeUpdate()
{
	min = glm::vec3(std::numeric_limits<float>::max());
	max = -glm::vec3(std::numeric_limits<float>::max());
}

void AABB::AfterUpdate()
{
	center = { (max + min) * 0.5f };
	extents = { max.x - center.x, max.y - center.y, max.z - center.z };

	float minToCheck = 0.01f;
	if (extents.x < minToCheck) extents.x = minToCheck;
	if (extents.y < minToCheck) extents.y = minToCheck;
	if (extents.z < minToCheck) extents.z = minToCheck;
}

std::array<glm::vec3, 8> AABB::getVertice() const
{
	std::array<glm::vec3, 8> vertice;
	vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
	return vertice;
}

bool AABB::IsOnOrForwardPlane(const Plane& plane) const
{
	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	const float r = extents.x * std::abs(plane.normal.x) + extents.y * std::abs(plane.normal.y) +
		extents.z * std::abs(plane.normal.z);

	return -r <= plane.GetSignedDistanceToPlane(center);
}

bool AABB::IsOnFrustum(const Frustum& camFrustum, const glm::mat4& model, const glm::vec3& rightT, const glm::vec3& upT,
	const glm::vec3& forwardT) const
{
	//Get global scale thanks to our transform
	const glm::vec3 globalCenter{ model * glm::vec4(center, 1.f) };

	// Scaled orientation
	const glm::vec3 right = rightT * extents.x;
	const glm::vec3 up = upT * extents.y;
	const glm::vec3 forward = forwardT * extents.z;

	const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

	const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

	const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

	const AABB globalAABB(globalCenter, newIi, newIj, newIk);

	return (globalAABB.IsOnOrForwardPlane(camFrustum.leftFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.rightFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.topFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.bottomFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.nearFace) &&
		globalAABB.IsOnOrForwardPlane(camFrustum.farFace));
}

bool AABB::IsOnFrustum(const Frustum& camFrustum, AABB* aabb) const
{
	const int maxPoints = 8;
	const int maxPlanes = 6;

	glm::vec3 points[maxPoints];
	points[0] = center + glm::vec3(extents.x, extents.y, extents.z);
	points[1] = center + glm::vec3(extents.x, extents.y, -extents.z);
	points[2] = center + glm::vec3(extents.x, -extents.y, extents.z);
	points[3] = center + glm::vec3(extents.x, -extents.y, -extents.z);
	points[4] = center + glm::vec3(-extents.x, extents.y, extents.z);
	points[5] = center + glm::vec3(-extents.x, extents.y, -extents.z);
	points[6] = center + glm::vec3(-extents.x, -extents.y, extents.z);
	points[7] = center + glm::vec3(-extents.x, -extents.y, -extents.z);

	Plane planes[maxPlanes];
	planes[0] = camFrustum.topFace;
	planes[1] = camFrustum.bottomFace;
	planes[2] = camFrustum.leftFace;
	planes[3] = camFrustum.rightFace;
	planes[4] = camFrustum.farFace;
	planes[5] = camFrustum.nearFace;

	for (int i = 0; i < maxPlanes; ++i)
	{
		int counterPointFarPlanes = 0;
		for (int j = 0; j < maxPoints; ++j)
		{
			float signedDistance = planes[i].GetSignedDistanceToPlane(points[j]);
			if (signedDistance < 0) { counterPointFarPlanes++; }
		}

		if (counterPointFarPlanes >= maxPoints)
			return false;
	}

	return true;
}