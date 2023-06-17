#include "Transform.h"
#include "GameObject.h"
#include <iostream>
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
	worldRotation = QuatToEuler(glm::quat_cast(modelMatrix));
	worldScale = { glm::length(glm::vec3(modelMatrix[0])),	glm::length(glm::vec3(modelMatrix[1])),	glm::length(glm::vec3(modelMatrix[2])) };
			
	aabb->BeforeUpdate();
	OnUpdateModelMatrix.Invoke();
	aabb->AfterUpdate();
}

// ============================================ TOOLS ============================================

glm::quat Transform::EulerToQuat(glm::vec3 euler)
{
	euler *= deg2rad;
	float cy = cos(euler.z * 0.5f);
	float sy = sin(euler.z * 0.5f);
	float cp = cos(euler.x * 0.5f);
	float sp = sin(euler.x * 0.5f);
	float cr = cos(euler.y * 0.5f);
	float sr = sin(euler.y * 0.5f);
	glm::quat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = cr * sp * cy + sr * cp * sy;
	q.y = sr * cp * cy - cr * sp * sy;
	q.z = cr * cp * sy - sr * sp * cy;
	return q;
}

glm::vec3 Transform::QuatToVec(glm::quat quat, glm::vec3 vec)
{
	float x2 = quat.x * 2.f;
	float y2 = quat.y * 2.f;
	float z2 = quat.z * 2.f;
	float xx2 = quat.x * x2;
	float yy2 = quat.y * y2;
	float zz2 = quat.z * z2;
	float xy2 = quat.x * y2;
	float xz2 = quat.x * z2;
	float yz2 = quat.y * z2;
	float wx2 = quat.w * x2;
	float wy2 = quat.w * y2;
	float wz2 = quat.w * z2;
	glm::vec3 res;
	res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
	res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
	res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
	return res;
}

glm::vec3 Transform::QuatToEuler(glm::quat rot)
{
	float sqw = rot.w * rot.w;
	float sqx = rot.x * rot.x;
	float sqy = rot.y * rot.y;
	float sqz = rot.z * rot.z;
	float unit = sqx + sqy + sqz + sqw;
	float test = rot.x * rot.w - rot.y * rot.z;
	glm::vec3 v = glm::vec3();
	if (test > 0.4995f * unit)
	{
		v.y = 2.f * atan2(rot.y, rot.x);
		v.x = glm::pi<float>() / 2.f;
		v.z = 0.f;
		return NormalizeAngles(v * rad2deg);
	}
	if (test < -0.4995f * unit)
	{
		v.y = -2.f * atan2(rot.y, rot.x);
		v.x = -glm::pi<float>() / 2.f;
		v.z = 0.f;
		return NormalizeAngles(v * rad2deg);
	}
	glm::vec4 q = glm::vec4(rot.w, rot.z, rot.x, rot.y);
	v.y = atan2(2.f * q.x * q.w + 2.f * q.y * q.z, 1.f - 2.f * (q.z * q.z + q.w * q.w));
	v.x = asin(2.f * (q.x * q.z - q.w * q.y));
	v.z = atan2(2.f * q.x * q.y + 2.f * q.z * q.w, 1.f - 2.f * (q.y * q.y + q.z * q.z));
	return NormalizeAngles(v * 57.29578f);
}

glm::vec3 Transform::NormalizeAngles(glm::vec3 angles)
{
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}

float Transform::NormalizeAngle(float angle)
{
	while (angle > 360.f)
		angle -= 360.f;
	while (angle < 0.f)
		angle += 360.f;
	return angle;
}