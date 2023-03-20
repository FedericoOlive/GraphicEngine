#include "Entity2D.h"
#include <algorithm>
#include <math.h>
#include <windows.h>

Entity2D::Entity2D() : Entity()
{
	
}

void Entity2D::SetCollisionManager(CollisionManager* collisionManager)
{
	this->collisionManager = collisionManager;
}

CollisionType Entity2D::CheckCollision(Entity2D& target, float& xOverlap, float& yOverlap)
{
	xOverlap = max(0.0f,
		min(transform->GetWorldPosition().x + fabs(transform->GetScale().x) / 2.0f, 
			target.transform->GetWorldPosition().x + fabs(target.transform->GetScale().x) / 2.0f) -
		max(transform->GetWorldPosition().x - fabs(transform->GetScale().x) / 2.0f, 
			target.transform->GetWorldPosition().x - fabs(target.transform->GetScale().x) / 2.0f));
	
	yOverlap = max(0.0f,
		min(transform->GetWorldPosition().y + fabs(transform->GetScale().y) / 2.0f, 
			target.transform->GetWorldPosition().y + fabs(target.transform->GetScale().y) / 2.0f) -
		max(transform->GetWorldPosition().y - fabs(transform->GetScale().y) / 2.0f, 
			target.transform->GetWorldPosition().y - fabs(target.transform->GetScale().y) / 2.0f));

	if (xOverlap != 0.0f && yOverlap != 0.0f)
	{
		if (xOverlap > yOverlap)
		{
			if (transform->GetWorldPosition().y < 0 && transform->GetWorldPosition().y < target.transform->GetWorldPosition().y || 
				transform->GetWorldPosition().y > 0 && transform->GetWorldPosition().y < target.transform->GetWorldPosition().y)
			{
				return CollisionType::up;
			}

			if (transform->GetWorldPosition().y < 0 && transform->GetWorldPosition().y > target.transform->GetWorldPosition().y || 
				transform->GetWorldPosition().y > 0 && transform->GetWorldPosition().y > target.transform->GetWorldPosition().y)
			{
				return CollisionType::down;
			}
		}
		else
		{
			if (transform->GetWorldPosition().x < 0 && transform->GetWorldPosition().x < target.transform->GetWorldPosition().x ||
				transform->GetWorldPosition().x > 0 && transform->GetWorldPosition().x < target.transform->GetWorldPosition().x)
			{
				return CollisionType::right;
			}

			if (transform->GetWorldPosition().x < 0 && transform->GetWorldPosition().x > target.transform->GetWorldPosition().x || 
				transform->GetWorldPosition().x > 0 && transform->GetWorldPosition().x > target.transform->GetWorldPosition().x)
			{
				return CollisionType::left;
			}
		}
	}

	return CollisionType::none;
}

void Entity2D::ApplyCollisionRestrictions(CollisionType colType, float xOverlap, float yOverlap, bool halfOverlap)
{
	float defYOverlap = halfOverlap ? yOverlap / 2 : yOverlap;
	float defXOverlap = halfOverlap ? xOverlap / 2 : xOverlap;
	glm::vec3 newPos = { 0,0,0 };
	switch (colType)
	{
	case CollisionType::up:
		newPos = { transform->GetWorldPosition().x,
					transform->GetWorldPosition().y - defYOverlap,
					transform->GetWorldPosition().z };
		transform->SetWorldPosition(newPos);
		break;
	case CollisionType::down:
		newPos = { transform->GetWorldPosition().x,
					transform->GetWorldPosition().y + defYOverlap,
					transform->GetWorldPosition().z };
		transform->SetWorldPosition(newPos);
		break;
	case CollisionType::left:
		newPos = { transform->GetWorldPosition().x + defXOverlap,
					transform->GetWorldPosition().y,
					transform->GetWorldPosition().z };
		transform->SetWorldPosition(newPos);
		break;
	case CollisionType::right:
		newPos = { transform->GetWorldPosition().x - defXOverlap,
					transform->GetWorldPosition().y,
					transform->GetWorldPosition().z };
		transform->SetWorldPosition(newPos);
		break;
	case CollisionType::none:
	default:
		break;
	}
}