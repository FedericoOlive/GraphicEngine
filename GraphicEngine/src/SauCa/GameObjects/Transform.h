#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <list>
#include <string>

#include "Exports.h"
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

	glm::vec3 worldScale;
	glm::vec3 localScale;
	
	void RemoveChildren(Transform* transformParent);
	void SetChildren(Transform* transformChildren);
	void UpdateModelMatrix();
	void UpdateTranslateMatrix();
	void UpdateRotationMatrix();
	void UpdateScaleMatrix();
	void UpdateChildTranslateMatrix();
	void UpdateChildRotationMatrix();
	void UpdateChildScaleMatrix();

public:
	
	std::list<Transform*> childrens;
	Transform* parent;
	GameObject* gameObject;

	const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;
	const float rad2deg = 360.0f / (glm::pi<float>() * 2.0f);

	glm::vec3 forward() const { return -modelMatrix[2]; }
	glm::vec3 right() const { return modelMatrix[0]; }
	glm::vec3 up() const { return modelMatrix[1]; }
	
	Event<> OnUpdateModelMatrix;
	Transform(GameObject* go);
	~Transform();

	void SetParent(Transform* parentTransform);
	void SetParent(GameObject* gameObject);
	Transform* GetParent() const { return parent; }
	std::list<Transform*> GetChildrens() const { return childrens; }
		
	void SetWorldPosition(glm::vec3 position);
	void SetLocalPosition(glm::vec3 position);
	
	void SetWorldRotation(glm::vec3 rotation);
	void SetLocalRotation(glm::vec3 rotation);
	
	void SetLocalScale(glm::vec3 scale);
	void SetWorldScale(glm::vec3 scale);

	// Vector 3
	glm::vec3 GetLocalPosition() const { return localPosition; }
	glm::vec3 GetWorldPosition() const { return worldPosition; }
	
	glm::vec3 GetLocalRotation() const { return localRotation; }
	glm::vec3 GetWorldRotation() const { return worldRotation; }
	
	glm::vec3 GetLocalScale() const { return localScale; }
	glm::vec3 GetWorldScale() const { return worldScale; }

	// Matrix
	glm::mat4 GetModelMatrix() const { return modelMatrix; }
	
	glm::mat4 GetTranslateMatrix() const { return translateMatrix; }
	glm::mat4 GetRotationMatrix() const { return rotationMatrix; }
	glm::mat4 GetScaleMatrix() const { return scaleMatrix; }

	// Tools
	glm::quat EulerToQuat(glm::vec3 euler);
	glm::vec3 QuatToVec(glm::quat quat, glm::vec3 vec);
	glm::vec3 QuatToEuler(glm::quat rot);
	glm::vec3 NormalizeAngles(glm::vec3 angles);
	float NormalizeAngle(float angle);
};

#endif