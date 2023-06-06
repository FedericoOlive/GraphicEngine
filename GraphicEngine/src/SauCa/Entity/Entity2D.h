#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "Entity.h"
class CollisionManager;

class SAUCA_API Entity2D : public Entity
{
private:
	CollisionManager* collisionManager;

public:
	Entity2D();
	void SetCollisionManager(CollisionManager* colManager);
	CollisionType CheckCollision(Entity2D& target, float& xOverlap, float& yOverlap);
	void ApplyCollisionRestrictions(CollisionType colType, float xOverlap, float yOverlap, bool halfOverlap);
};

#endif