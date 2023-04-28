#ifndef CAMERA_H
#define CAMERA_H

#include "Exports.h"
#include "GameObjects/Component.h"
#include "glm/glm/gtc/type_ptr.hpp"

class SAUCA_API  Camera : public Component
{
public:
	enum CameraType { Perspective, Orthogonal };
	glm::vec2 viewportPosition;
	glm::vec2 viewportSize;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	float aspect;
	
	Camera(glm::vec2 viewportPosition, glm::vec2 viewportSize, CameraType cameraType = Perspective);
	~Camera();

	void SetCameraOrthogonal(int width = 1280, int height = 720, float near = 0.0f, float far = 1000.0f);
	void SetCameraPerspective(float fov = 45.0f, float near = 0.1f, float far = 1000.0f);
	void OnAsigned() override;
	void OnUpdatePosition();
	void UpdateViewMatrix();
};

#endif