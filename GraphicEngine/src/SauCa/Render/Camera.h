#ifndef CAMERA_H
#define CAMERA_H

#include "Exports.h"
#include "GameObjects/Component.h"
#include "glm/glm/gtc/type_ptr.hpp"

class SAUCA_API  Camera : public Component
{
private:
	// Todo: Agregar comportamiento de movimiento (No se actualizan las matrices)
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 100.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

public:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	float aspect;
	float distanceOffset;
	float heightOffset = 100.0f;
	GameObject* target;
	
	Camera(int width, int height);
	~Camera();

	void SetCameraOrthogonal(int width, int height, float near = 0.0f, float far = 1000.0f);
	void SetCameraPerspective(float fov = 45.0f, float near = 0.1f, float far = 1000.0f);
	void OnAsigned() override;
	void OnUpdatePosition();
};

#endif