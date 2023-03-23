#include "Camera.h"
#include "Renderer.h"
#include "GameObjects/GameObject.h"

Camera::Camera(int width, int height)
{
	target = nullptr;
	aspect = (float)width / (float)height;
	viewMatrix = glm::lookAt(cameraPos, cameraTarget, up);
	SetCameraPerspective();
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

void Camera::OnAsigned()
{
	std::function<void()> onUpdatePosition = [this] { OnUpdatePosition(); };
	gameobject->transform->OnUpdateModelMatrix.AddListener(onUpdatePosition);
}

void Camera::OnUpdatePosition()
{
	cameraPos = gameobject->transform->GetWorldPosition();

	if (target == nullptr)
	{
		viewMatrix = glm::lookAt(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->forward, up);
	}
	else
	{
		viewMatrix = glm::lookAt(transform->GetWorldPosition() + offsetViewport*transform->forward, target->transform->GetWorldPosition(), up);
	}
}