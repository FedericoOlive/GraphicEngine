#include "CollisionManager.h"

std::list<Entity*> CollisionManager::entitiesCollision;

bool CollisionManager::IsCollision2DRecRec(Entity* entity1, Entity* entity2)
{
    glm::vec2 pos1 = glm::vec2(entity1->GetPosition().x - entity1->GetScale().x / 2, entity1->GetPosition().y - entity1->GetScale().y / 2);
    glm::vec2 pos2 = glm::vec2(entity2->GetPosition().x - entity2->GetScale().x / 2, entity2->GetPosition().y - entity2->GetScale().y / 2);
	
    return (pos1.x < pos2.x + entity2->GetScale().x &&
        pos1.x + entity1->GetScale().x > pos2.x &&
        pos1.y < pos2.y + entity2->GetScale().y &&
        pos1.y + entity1->GetScale().y > pos2.y);
}

void CollisionManager::AddToList(Entity* entity)
{
    entitiesCollision.push_back(entity);
}