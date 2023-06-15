#ifndef COLLISIONMANAGER3D_H
#define COLLISIONMANAGER3D_H

#include "Collider.h"
#include <list>

class SAUCA_API CollisionManager3D
{
public:
	std::list<Collider*> dynamicCollisionList;
	std::list<Collider*> staticCollisionList;

	static bool IsCollision(Transform* collider1, Transform* collider2);
	static bool IsCollision(Collider* collider1, Collider* collider2);
	void AddToCollisionList(Collider* colliderToAdd, bool isStatic);
	void RemoveFromCollisionList(Collider* colliderToRemove);
	bool IsInCollisionList(Collider* colliderToCheck);
	void UpdateCollisions();
};

#endif