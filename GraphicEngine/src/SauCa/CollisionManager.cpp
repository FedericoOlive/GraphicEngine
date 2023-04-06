#include "CollisionManager.h"

bool CollisionManager::IsCollision2DRecRec(Entity2D* entity1, Entity2D* entity2)
{
    glm::vec2 pos1 = glm::vec2(entity1->transform->GetWorldPosition().x - entity1->transform->GetLocalScale().x / 2, 
								entity1->transform->GetWorldPosition().y - entity1->transform->GetLocalScale().y / 2);
    glm::vec2 pos2 = glm::vec2(entity2->transform->GetWorldPosition().x - entity2->transform->GetLocalScale().x / 2, 
								entity2->transform->GetWorldPosition().y - entity2->transform->GetLocalScale().y / 2);
	
    return (pos1.x < pos2.x + entity2->transform->GetLocalScale().x &&
        pos1.x + entity1->transform->GetLocalScale().x > pos2.x &&
        pos1.y < pos2.y + entity2->transform->GetLocalScale().y &&
        pos1.y + entity1->transform->GetLocalScale().y > pos2.y);
}

void CollisionManager::AddToCollisionList(Entity2D* entityToAdd, bool isStatic)
{
	entityToAdd->SetCollisionManager(this);

	if (isStatic)
		staticCollisionList.push_back(entityToAdd);
	else
		dynamicCollisionList.push_back(entityToAdd);
}

void CollisionManager::RemoveFromCollisionList(Entity2D* entityToRemove)
{
	staticCollisionList.remove(entityToRemove);
	dynamicCollisionList.remove(entityToRemove);
}

bool CollisionManager::IsInCollisionList(Entity2D* entityToCheck)
{
	for (auto const& d1 : dynamicCollisionList) 
	{
		if (d1 == entityToCheck) 
			return true;
	}
	for (auto const& s1 : staticCollisionList) 
	{
		if (s1 == entityToCheck) 
			return true;
	}
	return false;
}

void CollisionManager::UpdateCollisions()
{

	for (auto const& d1 : dynamicCollisionList) {
		for (auto const& d2 : dynamicCollisionList) {
			if (d1 != d2)
			{
				float overlapX = 0;
				float overlapY = 0;
				CollisionType currentCollision = d1->CheckCollision(*d2, overlapX, overlapY);
				if (currentCollision != CollisionType::none)
				{
					d1->ApplyCollisionRestrictions(currentCollision, overlapX, overlapY, true);
					d2->ApplyCollisionRestrictions(currentCollision, -overlapX, -overlapY, true);
				}
			}
		}
	}

	for (auto const& d : dynamicCollisionList) {
		for (auto const& s : staticCollisionList) {
			float overlapX = 0;
			float overlapY = 0;
			CollisionType currentCollision = d->CheckCollision(*s, overlapX, overlapY);
			if (currentCollision != CollisionType::none)
			{
				d->ApplyCollisionRestrictions(currentCollision, overlapX, overlapY, false);
			}
		}
	}
}

void CollisionManager::UpdateCollisionsInTileMap(TileMap* tileMap)
{
	for (auto const& d1 : dynamicCollisionList) {
		for (auto const& d2 : dynamicCollisionList) {
			if (d1 != d2)
			{
				tileMap->CheckCollision(*d1);
				tileMap->CheckCollision(*d2);

				float overlapX = 0;
				float overlapY = 0;
				CollisionType currentCollision = d1->CheckCollision(*d2, overlapX, overlapY);

				if (currentCollision != CollisionType::none)
				{
					d1->ApplyCollisionRestrictions(currentCollision, overlapX, overlapY, true);
					d2->ApplyCollisionRestrictions(currentCollision, -overlapX, -overlapY, true);
				}
			}
			else
			{
				tileMap->CheckCollision(*d1);
			}
		}
	}
}