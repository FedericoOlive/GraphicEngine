#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Exports.h"
#include "Entity/Entity2D.h"
#include<list>

class SAUCA_API CollisionManager
{
private:

public:
	static std::list<Entity*> entitiesCollision;
	static bool IsCollision2DRecRec(Entity* entity1, Entity* entity2);
	static void AddToList(Entity* entity);
};

#endif