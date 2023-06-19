#ifndef AABB_H
#define AABB_H

#include "BoundingVolume.h"
#include <array>
#include <iostream>

struct SAUCA_API AABB : public BoundingVolume
{
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 center{ 0.0f, 0.0f, 0.0f };
	glm::vec3 extents{ 0.01f, 0.01f, 0.01f };

	AABB() {}
	AABB(const glm::vec3& min, const glm::vec3& max)
		: BoundingVolume{}, center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z }
	{}

	AABB(const glm::vec3& inCenter, float iI, float iJ, float iK)
		: BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK }
	{}

	void BeforeUpdate();
	void AfterUpdate(std::string nameGameObject);
	std::array<glm::vec3, 8> getVertice() const;
	
	//see https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html
	bool IsOnOrForwardPlane(const Plane& plane) const final;
	bool IsOnFrustum(const Frustum& camFrustum, const glm::mat4& model, const glm::vec3& rightT, const glm::vec3& upT, const glm::vec3& forwardT) const final;
	bool IsOnFrustum(const Frustum& camFrustum, AABB* aabb) const;
};

#endif