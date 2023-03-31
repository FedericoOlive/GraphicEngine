#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <list>
#include "Exports.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "Utility/Event.h"

class SAUCA_API Transform
{
protected:
	glm::mat4 modelMatrix;

	glm::mat4 translateMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	glm::vec3 worldPosition;
	glm::vec3 localPosition;
	
	glm::vec3 worldRotation;
	glm::vec3 localRotation;

	glm::vec3 scale;
	
	Transform* parent;
	std::list<Transform*> childrens;

	void RemoveChildren(Transform* transformParent);
	void SetChildren(Transform* transformChildren);
	void UpdateModelMatrix();
	void UpdateTranslateMatrix();
	void UpdateRotationMatrix();
	void UpdateChildTranslateMatrix();
	void UpdateChildRotationMatrix();
	void UpdateChildScaleMatrix();
	void UpdateDirectionVectors();

public:

	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	
	Event<> OnUpdateModelMatrix;
	Transform();
	~Transform();

	void SetParent(Transform* parentTransform);
	void SetParent(GameObject* gameObject);
	Transform* GetParent() const { return parent; }
	std::list<Transform*> GetChildrens() const { return childrens; }
		
	void SetWorldPosition(glm::vec3 position);
	void SetLocalPosition(glm::vec3 position);
	
	void SetWorldRotation(glm::vec3 rotation);
	void SetLocalRotation(glm::vec3 rotation);
	
	void SetScale(glm::vec3 scale);

	// Vector 3
	glm::vec3 GetLocalPosition() const { return localPosition; }
	glm::vec3 GetWorldPosition() const { return worldPosition; }
	glm::vec3 GetLocalRotation() const { return localRotation; }
	glm::vec3 GetWorldRotation() const { return worldRotation; }
	
	glm::vec3 GetScale() const { return scale; }

	// Matrix
	glm::mat4 GetModelMatrix() const { return modelMatrix; }
	
	glm::mat4 GetTranslateMatrix() const { return translateMatrix; }
	glm::mat4 GetRotationMatrix() const { return rotationMatrix; }
	glm::mat4 GetScaleMatrix() const { return scaleMatrix; }
};

#endif