#include "Camera.h"
#include "Renderer.h"

Camera::Camera(int width, int height)
{
	aspect = (float)width / (float)height;
	viewMatrix = glm::lookAt(cameraPos, cameraTarget, up);
	SetCameraPerspective(45.0f, 0.1f, 1000.0f);
	//SetCameraOrthogonal(1280, 720);
	Renderer::AddCamera(this);
}

Camera::~Camera()
{
	Renderer::RemoveCamera(this);
}

void Camera::SetCameraOrthogonal(int width, int height, float near, float far)
{
	projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, near, far);
}

void Camera::SetCameraPerspective(float fov, float near, float far)
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}