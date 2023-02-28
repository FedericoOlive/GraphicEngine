#include "Entity2D.h"
#include <algorithm>
#include <math.h>
#include <windows.h>

Entity2D::Entity2D()
{
	
}

void Entity2D::SetCollisionManager(CollisionManager* collisionManager)
{
	this->collisionManager = collisionManager;
}

CollisionType Entity2D::CheckCollision(Entity2D& target, float& xOverlap, float& yOverlap)
{
	xOverlap = max(0.0f,
		min(GetPosition().x + fabs(GetScale().x) / 2.0f, target.GetPosition().x + fabs(target.GetScale().x) / 2.0f) -
		max(GetPosition().x - fabs(GetScale().x) / 2.0f, target.GetPosition().x - fabs(target.GetScale().x) / 2.0f));
	
	yOverlap = max(0.0f,
		min(GetPosition().y + fabs(GetScale().y) / 2.0f, target.GetPosition().y + fabs(target.GetScale().y) / 2.0f) -
		max(GetPosition().y - fabs(GetScale().y) / 2.0f, target.GetPosition().y - fabs(target.GetScale().y) / 2.0f));

	if (xOverlap != 0.0f && yOverlap != 0.0f)
	{
		if (xOverlap > yOverlap)
		{
			if (GetPosition().y < 0 && GetPosition().y < target.GetPosition().y || GetPosition().y > 0 && GetPosition().y < target.GetPosition().y)
			{
				return CollisionType::up;
			}

			if (GetPosition().y < 0 && GetPosition().y > target.GetPosition().y || GetPosition().y > 0 && GetPosition().y > target.GetPosition().y)
			{
				return CollisionType::down;
			}
		}
		else
		{
			if (GetPosition().x < 0 && GetPosition().x < target.GetPosition().x || GetPosition().x > 0 && GetPosition().x < target.GetPosition().x)
			{
				return CollisionType::right;
			}

			if (GetPosition().x < 0 && GetPosition().x > target.GetPosition().x || GetPosition().x > 0 && GetPosition().x > target.GetPosition().x)
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

	switch (colType)
	{
	case CollisionType::up:
		SetPosition(GetPosition().x, GetPosition().y - defYOverlap, GetPosition().z);
		break;
	case CollisionType::down:
		SetPosition(GetPosition().x, GetPosition().y + defYOverlap, GetPosition().z);
		break;
	case CollisionType::left:
		SetPosition(GetPosition().x + defXOverlap, GetPosition().y, GetPosition().z);
		break;
	case CollisionType::right:
		SetPosition(GetPosition().x - defXOverlap, GetPosition().y, GetPosition().z);
		break;
	case CollisionType::none:
	default:
		break;
	}
}