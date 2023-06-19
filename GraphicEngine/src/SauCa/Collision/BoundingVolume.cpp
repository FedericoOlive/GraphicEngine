#include "BoundingVolume.h"

bool BoundingVolume::IsOnFrustum(const Frustum& camFrustum) const
{
	return (IsOnOrForwardPlane(camFrustum.leftFace) &&
		IsOnOrForwardPlane(camFrustum.rightFace) &&
		IsOnOrForwardPlane(camFrustum.topFace) &&
		IsOnOrForwardPlane(camFrustum.bottomFace) &&
		IsOnOrForwardPlane(camFrustum.nearFace) &&
		IsOnOrForwardPlane(camFrustum.farFace));
}