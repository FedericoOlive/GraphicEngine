#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <list>
#include "Exports.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

class SAUCA_API Transform
{
protected:
	glm::mat4 modelMatrix;

	glm::mat4 translateMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	glm::vec3 localPosition;
	glm::vec3 worldPosition;
	glm::vec3 worldRotation;
	glm::vec3 worldScale;

	Transform* parent;
	std::list<Transform*> childrens;

	void RemoveChildren(Transform* transformParent);
	void SetChildren(Transform* transformChildren);
	void UpdatePosition();
	void UpdateModelMatrix();

public:
	Transform();
	~Transform();

	void SetParent(Transform* parentTransform);
	Transform* GetParent() const { return parent; }
	std::list<Transform*> GetChildrens() const { return childrens; }
		
	void SetLocalPosition(glm::vec3 position);
	void SetWorldPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	// Vector 3
	glm::vec3 GetLocalPosition() const { return localPosition; }
	glm::vec3 GetWorldPosition() const { return worldPosition; }
	glm::vec3 GetRotation() const { return worldRotation; }
	glm::vec3 GetScale() const { return worldScale; }

	// Matrix
	glm::mat4 GetModelMatrix() const { return modelMatrix; }
	
	glm::mat4 GetTranslateMatrix()const { return translateMatrix; }
	glm::mat4 GetRotationMatrix() const { return rotationMatrix; }
	glm::mat4 GetScaleMatrix() const { return scaleMatrix; }
};

#endif