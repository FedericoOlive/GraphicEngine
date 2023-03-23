#include "Transform.h"

#include "GameObject.h"

Transform::Transform()
{
	modelMatrix = glm::mat4(1.0f);
	translateMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

	localPosition = glm::vec3(0.0f);
	worldPosition = glm::vec3(0.0f);
	worldRotation = glm::vec3(0.0f);
	worldScale = glm::vec3(1.0f);


	parent = nullptr;
	//childrens;
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

void Transform::UpdatePosition()
{
	worldPosition = parent->worldPosition + localPosition;

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdatePosition();
	}
}

void Transform::UpdateModelMatrix()
{
	forward.x = cos(glm::radians(worldRotation.y)) * cos(glm::radians(worldRotation.x));
	forward.y = sin(glm::radians(worldRotation.x));
	forward.z = sin(glm::radians(worldRotation.y)) * cos(glm::radians(worldRotation.x));

	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, forward));
	
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
	OnUpdateModelMatrix.Invoke();
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

void Transform::SetLocalPosition(glm::vec3 position)
{
	localPosition = position;
	
	if (parent != nullptr)
		worldPosition = parent->worldPosition + localPosition;
	else
		worldPosition = localPosition;

	translateMatrix = glm::mat4(1.0f);
	translateMatrix = glm::translate(translateMatrix, worldPosition);
	UpdateModelMatrix();
}

void Transform::SetWorldPosition(glm::vec3 position)
{
	worldPosition = position;

	if (parent != nullptr)
		localPosition = worldPosition - parent->worldPosition;
	else
		localPosition = worldPosition;

	for (auto iter = childrens.begin(); iter != childrens.end(); ++iter)
	{
		(*iter)->UpdatePosition();
	}

	translateMatrix = glm::mat4(1.0f);
	translateMatrix = glm::translate(translateMatrix, worldPosition);
	
	UpdateModelMatrix();
}

void Transform::SetRotation(glm::vec3 rotation)
{
	worldRotation = rotation;
	rotationMatrix = glm::mat4(1.0f);
	
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	UpdateModelMatrix();
}

void Transform::SetScale(glm::vec3 scale)
{
	worldScale = scale;
	scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, scale);
	
	UpdateModelMatrix();
}