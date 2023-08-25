#include "Entity.h"

Entity::Entity() : Component()
{
	vertexData = nullptr;
	isRenderizable = true;
	alpha = 1.0f;
}

Entity::~Entity()
{
	if (vertexData != nullptr)
	{
		delete vertexData;
		vertexData = nullptr;
	}

	if (!material->flagDestroyed)
	{
		material->flagDestroyed = true;
		delete material;
		material = nullptr;
	}
}

void Entity::SetRenderer(Renderer* render)
{
	this->renderer = render;
}

void Entity::SetColorTint(float r, float g, float b, float a)
{
	material->colorTint = glm::vec3(r, g, b);
	alpha = a;
}

//void Entity::OnAsigned()
//{
//	std::function<void()> recalculateAABB = [this] { RecalculateAABB(); };
//	transform->OnUpdateModelMatrix.AddListener(recalculateAABB);
//}
//
//void Entity::RecalculateAABB()
//{
//	
//}

void Entity::CalculateParentAABB()
{
	Transform* parent = transform->parent;
	
	while (parent != nullptr)
	{
		parent->aabbGlobal->min.x = glm::min(transform->aabbGlobal->min.x, parent->aabbGlobal->min.x);
		parent->aabbGlobal->min.y = glm::min(transform->aabbGlobal->min.y, parent->aabbGlobal->min.y);
		parent->aabbGlobal->min.z = glm::min(transform->aabbGlobal->min.z, parent->aabbGlobal->min.z);
		parent->aabbGlobal->max.x = glm::max(transform->aabbGlobal->max.x, parent->aabbGlobal->max.x);
		parent->aabbGlobal->max.y = glm::max(transform->aabbGlobal->max.y, parent->aabbGlobal->max.y);
		parent->aabbGlobal->max.z = glm::max(transform->aabbGlobal->max.z, parent->aabbGlobal->max.z);
		parent->aabbGlobal->AfterUpdate();

		transform->aabbLocal->min = transform->aabbGlobal->min;
		transform->aabbLocal->max = transform->aabbGlobal->max;
		transform->aabbLocal->AfterUpdate();

		parent = parent->parent;
	}
}