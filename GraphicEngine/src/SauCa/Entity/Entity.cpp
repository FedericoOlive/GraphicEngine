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
	if (material != nullptr)
	{
		delete material;
		material = nullptr;
	}
}

void Entity::SetRenderer(Renderer* renderer)
{
	this->renderer = renderer;
}

void Entity::SetColorTint(float r, float g, float b, float a)
{
	material->colorTint = glm::vec3(r, g, b);
	alpha = a;
}

void Entity::OnAsigned()
{
	std::function<void()> recalculateAABB = [this] { RecalculateAABB(); };
	transform->OnUpdateModelMatrix.AddListener(recalculateAABB);
}

void Entity::RecalculateAABB()
{
	
}

void Entity::CalculateAABB()
{
	Transform* parent = transform->parent;
	
	//while (parent != nullptr)
	//{
	//	parent->aabb->min.x = glm::min(transform->aabb->min.x, parent->aabb->min.x);
	//	parent->aabb->min.y = glm::min(transform->aabb->min.y, parent->aabb->min.y);
	//	parent->aabb->min.z = glm::min(transform->aabb->min.z, parent->aabb->min.z);
	//	parent->aabb->max.x = glm::max(transform->aabb->max.x, parent->aabb->max.x);
	//	parent->aabb->max.y = glm::max(transform->aabb->max.y, parent->aabb->max.y);
	//	parent->aabb->max.z = glm::max(transform->aabb->max.z, parent->aabb->max.z);
	//	parent = parent->parent;
	//}
}
