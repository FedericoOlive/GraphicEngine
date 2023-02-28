#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Entity/Entity2D/TileMap.h"
#include<list>

class Entity2D;


class SAUCA_API CollisionManager
{
protected:
	std::list<Entity2D*> dynamicCollisionList;
	std::list<Entity2D*> staticCollisionList;

public:
	
	bool IsCollision2DRecRec(Entity2D* entity1, Entity2D* entity2);
	void AddToCollisionList(Entity2D* entityToAdd, bool isStatic);
	void RemoveFromCollisionList(Entity2D* entityToRemove);
	bool IsInCollisionList(Entity2D* entityToCheck);
	void UpdateCollisions();
	void UpdateCollisionsInTileMap(TileMap* tileMap);
};

#endif