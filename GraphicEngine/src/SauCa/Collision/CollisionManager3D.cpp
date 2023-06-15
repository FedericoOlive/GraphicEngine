#include "CollisionManager3D.h"

#include "AABB.h"
#include "GameObjects/Transform.h"

bool CollisionManager3D::IsCollision(Transform* collider1, Transform* collider2)
{
	AABB* aabb1 = collider1->aabb;
	AABB* aabb2 = collider2->aabb;

	return( aabb1->max.x > aabb2->min.x &&
			aabb1->min.x < aabb2->max.x &&
			aabb1->max.y > aabb2->min.y &&
			aabb1->min.y < aabb2->max.y &&
			aabb1->max.z > aabb2->min.z &&
			aabb1->min.z < aabb2->max.z);
	
	if (aabb1->max.x < aabb2->min.x || aabb1->min.x > aabb2->max.x)
		return false;
	if (aabb1->max.y < aabb2->min.y || aabb1->min.y > aabb2->max.y)
		return false;
	if (aabb1->max.z < aabb2->min.z || aabb1->min.z > aabb2->max.z)
		return false;

	return true;
}

bool CollisionManager3D::IsCollision(Collider* collider1, Collider* collider2)
{
	return IsCollision(collider1->transform, collider2->transform);
}

void CollisionManager3D::AddToCollisionList(Collider* colliderToAdd, bool isStatic)
{
	if (isStatic)
		staticCollisionList.push_back(colliderToAdd);
	else
		dynamicCollisionList.push_back(colliderToAdd);
}

void CollisionManager3D::RemoveFromCollisionList(Collider* colliderToRemove)
{
	staticCollisionList.remove(colliderToRemove);
	dynamicCollisionList.remove(colliderToRemove);
}

bool CollisionManager3D::IsInCollisionList(Collider* colliderToCheck)
{
	for (auto const& d1 : dynamicCollisionList)
		if (d1 == colliderToCheck)
			return true;
	
	for (auto const& s1 : staticCollisionList)
		if (s1 == colliderToCheck)
			return true;
	
	return false;
}

void CollisionManager3D::UpdateCollisions()
{
	for (Collider*& d1 : dynamicCollisionList)
	{
		for (Collider*& d2 : dynamicCollisionList)
		{
			if (d1 != d2)
			{
				if (IsCollision(d1, d2))
				{

				}


				
				//float overlapX = 0;
				//float overlapY = 0;
				//
				//CollisionType currentCollision = d1->CheckCollision(*d2, overlapX, overlapY);
				//if (currentCollision != CollisionType::none)
				//{
				//	d1->ApplyCollisionRestrictions(currentCollision, overlapX, overlapY, true);
				//	d2->ApplyCollisionRestrictions(currentCollision, -overlapX, -overlapY, true);
				//}
			}
		}
	}

	for (Collider*& d : dynamicCollisionList) 
	{
		for (Collider*& s : staticCollisionList) 
		{
			float overlapX = 0;
			float overlapY = 0;
			//CollisionType currentCollision = d->CheckCollision(*s, overlapX, overlapY);
			//if (currentCollision != CollisionType::none)
			//{
			//	d->ApplyCollisionRestrictions(currentCollision, overlapX, overlapY, false);
			//}
		}
	}
}