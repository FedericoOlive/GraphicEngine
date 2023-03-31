#include "Transform.h"
#include "GameObject.h"
#include <iostream>
//https://developer.unigine.com/en/docs/latest/code/fundamentals/matrix_transformations/index?rlang=cpp
Transform::Transform()
{
	modelMatrix = glm::mat4(1.0f);
	translateMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

	localPosition = glm::vec3(0.0f);
	worldPosition = glm::vec3(0.0f);
	worldRotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

	parent = nullptr;
}

Transform::~Transform()
{

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
		parent->RemoveChildren(this);

	parent = parentTransform;
	if (parentTransform)
		parentTransform->SetChildren(this);
}

void Transform::SetParent(GameObject* gameObject)
{
	SetParent(gameObject->transform);
}

// ============================================ POSITION ============================================

void Transform::SetLocalPosition(glm::vec3 position)
{
	localPosition = position;
	worldPosition = (parent == nullptr) ? localPosition : parent->worldPosition + localPosition;

	UpdateTranslateMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildTranslateMatrix();
	}
}

void Transform::SetWorldPosition(glm::vec3 position)
{
	worldPosition = position;
	localPosition = (parent == nullptr) ? worldPosition : worldPosition - parent->worldPosition;

	UpdateTranslateMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildTranslateMatrix();
	}
}

void Transform::UpdateTranslateMatrix()
{
	translateMatrix = glm::mat4(1.0f);
	translateMatrix = glm::translate(translateMatrix, localPosition);
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
	worldRotation = rotation;
	localRotation = parent ? rotation - parent->worldRotation : rotation;
	UpdateDirectionVectors();
	UpdateRotationMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildRotationMatrix();
	}
}

void Transform::SetLocalRotation(glm::vec3 rotation)
{
	worldRotation = (parent == nullptr) ? rotation : parent->worldRotation + rotation;
	localRotation = rotation;
	UpdateDirectionVectors();
	UpdateRotationMatrix();
	UpdateModelMatrix();

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdateChildRotationMatrix();
	}
}

void Transform::UpdateDirectionVectors()
{
	forward.x = cos(glm::radians(localRotation.y)) * cos(glm::radians(localRotation.x));
	forward.y = sin(glm::radians(localRotation.x));
	forward.z = sin(glm::radians(localRotation.y)) * cos(glm::radians(localRotation.x));
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, forward));
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

void Transform::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	UpdateChildScaleMatrix();

	UpdateModelMatrix();
}

void Transform::UpdateChildScaleMatrix()
{
	scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, scale);
}

// ============================================ MODEL ============================================

void Transform::UpdateModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
	if (parent)
		modelMatrix = modelMatrix * parent->modelMatrix;
	
	OnUpdateModelMatrix.Invoke();
}