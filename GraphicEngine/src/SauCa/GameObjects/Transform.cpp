#include "Transform.h"
#include "GameObject.h"
#include <iostream>
#include "Utility/Utility.h"

//https://developer.unigine.com/en/docs/latest/code/fundamentals/matrix_transformations/index?rlang=cpp
Transform::Transform(GameObject* go)
{
	parent = nullptr;
	gameObject = go;
	aabb = new AABB();
	
	localPosition = glm::vec3(0.0f);
	localRotation= glm::vec3(0.0f);
	localScale = glm::vec3(1.0f);
	
	UpdateTranslateMatrix();
	UpdateRotationMatrix();
	UpdateScaleMatrix();
	UpdateModelMatrix();	
}

Transform::~Transform()
{
	if (aabb != nullptr)
	{
		delete aabb;
		aabb = nullptr;
	}
}

void Transform::RemoveChildren(Transform* transformParent)
{
	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		if (*iter == transformParent)
		{
			childrens.erase(iter);
			break;
		}
	}
}

void Transform::SetChildren(Transform* transformChildren)
{
	childrens.push_back(transformChildren);
}

void Transform::SetParent(Transform* parentTransform)
{
	if (parent)
	{
		parent->RemoveChildren(this);
	}

	parent = parentTransform;
	
	if (parent)
	{	
		parent->SetChildren(this);
	}
}

void Transform::SetParent(GameObject* gameObject)
{
	SetParent(gameObject->transform);
}

void Transform::GetRecursivelyChildrens(std::list<Transform*>& allChildrens, bool excludeThis)
{
	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
		(*iter)->GetRecursivelyChildrens(allChildrens, false);

	if (!excludeThis)
		allChildrens.push_back(this);
}

// ============================================ POSITION ============================================

void Transform::SetLocalPosition(glm::vec3 position)
{
	localPosition = position;

	UpdateTranslateMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildTranslateMatrix();
	}
}

void Transform::SetWorldPosition(glm::vec3 position)
{
	localPosition = parent ? position - parent->worldPosition : position;

	UpdateTranslateMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildTranslateMatrix();
	}
}

void Transform::UpdateTranslateMatrix()
{
	translateMatrix = glm::translate(glm::mat4(1.0f), localPosition);
}

void Transform::UpdateChildTranslateMatrix()
{
	UpdateTranslateMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildTranslateMatrix();
	}
}

// ============================================ ROTATION ============================================

void Transform::SetWorldRotation(glm::vec3 rotation)
{
	localRotation = parent ? rotation - parent->worldRotation : rotation;
	
	UpdateRotationMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildRotationMatrix();
	}
}

void Transform::SetLocalRotation(glm::vec3 rotation)
{
	localRotation = rotation;
	
	UpdateRotationMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildRotationMatrix();
	}
}

void Transform::UpdateRotationMatrix()
{
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(localRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(localRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(localRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Transform::UpdateChildRotationMatrix()
{
	UpdateRotationMatrix();
	UpdateModelMatrix();
	
	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildRotationMatrix();
	}
}

// ============================================ SCALE ============================================

void Transform::SetLocalScale(glm::vec3 scale)
{
	localScale = scale;
	
	UpdateChildScaleMatrix();
	UpdateModelMatrix();
}

void Transform::SetWorldScale(glm::vec3 scale)
{
	localScale = parent ? scale - parent->worldScale : scale;
	
	UpdateChildScaleMatrix();
	UpdateModelMatrix();
}

void Transform::UpdateScaleMatrix()
{
	scaleMatrix = glm::scale(glm::mat4(1.0f), localScale);
}

void Transform::UpdateChildScaleMatrix()
{
	UpdateScaleMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildScaleMatrix();
	}
}

// ============================================ MODEL ============================================

void Transform::UpdateModelMatrix()
{
	modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
	if (parent)
		modelMatrix = parent->modelMatrix * modelMatrix;

	worldPosition = modelMatrix[3];
	worldRotation = Utility::QuatToEuler(glm::quat_cast(modelMatrix));
	worldScale = { glm::length(glm::vec3(modelMatrix[0])),	glm::length(glm::vec3(modelMatrix[1])),	glm::length(glm::vec3(modelMatrix[2])) };
			
	aabb->BeforeUpdate();
	OnUpdateModelMatrix.Invoke();
	//aabb->AfterUpdate(gameObject->name);
}