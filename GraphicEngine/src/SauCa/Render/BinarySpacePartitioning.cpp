#include "BinarySpacePartitioning.h"

Transform* BinarySpacePartitioning::target;
std::list<Transform*> BinarySpacePartitioning::planes;
bool BinarySpacePartitioning::isEnable = false;

bool BinarySpacePartitioning::SameSide(Transform* entity, Transform* plane)
{
	Plane bspPlane;
	bspPlane.SetPositionAndNormal(plane->GetWorldPosition(), plane->forward());
	bool sideEntity = bspPlane.GetSide(entity->GetWorldPosition());
	bool sideTarget = bspPlane.GetSide(target->GetWorldPosition());

	return sideEntity == sideTarget;
}

void BinarySpacePartitioning::SetTarget(Transform* newTarget)
{
	target = newTarget;
}

void BinarySpacePartitioning::AddPlane(Transform* plane)
{
	planes.push_back(plane);
}

bool BinarySpacePartitioning::IsDraweable(Transform* entity)
{
	if (isEnable)
		for (auto iter = planes.begin(); iter != planes.end(); ++iter)
			if (!SameSide(entity, *(iter)))
				return false;
	return true;
}