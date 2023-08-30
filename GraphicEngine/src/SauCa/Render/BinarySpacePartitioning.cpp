#include "BinarySpacePartitioning.h"

Transform* BinarySpacePartitioning::target;
std::list<Transform*> BinarySpacePartitioning::planes;
bool BinarySpacePartitioning::isEnable = false;

bool BinarySpacePartitioning::SameSide(Transform* entity, Transform* plane)
{
	Plane bspPlane;
	bspPlane.SetPositionAndNormal(plane->GetWorldPosition(), plane->forward());
	const bool sideTarget = bspPlane.GetSide(target->GetWorldPosition());

	return HasVertexInSideSameSide(entity, bspPlane, sideTarget);
}

bool BinarySpacePartitioning::HasVertexInSideSameSide(Transform* entity, Plane bspPlane, bool side)
{
	int const size = 8;
	std::array<glm::vec3, size> vertices = entity->aabbGlobal->getVertice();
	for (int i = 0; i < size; ++i)
	{
		if (bspPlane.GetSide(vertices[i]) == side)
			return true;
	}

	return false;
}

void BinarySpacePartitioning::SetTarget(Transform* newTarget)
{
	target = newTarget;
}

void BinarySpacePartitioning::AddPlane(Transform* plane)
{
	planes.push_back(plane);
}

bool BinarySpacePartitioning::IsDrawable(Transform* entity)
{
	if (isEnable)
		for (auto iter = planes.begin(); iter != planes.end(); ++iter)
			if (!SameSide(entity, *(iter)))
				return false;
	return true;
}