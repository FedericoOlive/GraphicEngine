#ifndef BOUNDING_VOLUME_H
#define BOUNDING_VOLUME_H

#include "Frustum.h"

struct SAUCA_API BoundingVolume
{
	virtual bool IsOnFrustum(const Frustum& camFrustum, const glm::mat4& model, const glm::vec3& rightT, const glm::vec3& upT, const glm::vec3& forwardT) const = 0;
	virtual bool IsOnOrForwardPlane(const Plane& plane) const = 0;
	bool IsOnFrustum(const Frustum& camFrustum) const;
};

#endif