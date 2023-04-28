#include "Camera.h"
#include "Renderer.h"
#include "GameObjects/GameObject.h"

Camera::Camera(glm::vec2 viewportPosition, glm::vec2 viewportSize, CameraType cameraType)
{
	aspect = viewportSize.x / viewportSize.y;
	this->viewportPosition = viewportPosition;
	this->viewportSize = viewportSize;
	//glViewport((GLint)viewportPosition.x, (GLint)viewportPosition.y, (GLint)viewportSize.x, (GLint)viewportSize.y);
	
	switch (cameraType)
	{
	case Perspective:
		SetCameraPerspective();
		break;
	case Orthogonal:
		SetCameraOrthogonal();
		break;
	default:
		SetCameraPerspective();
		break;
	}
	name = "Camera";

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
	UpdateViewMatrix();
}

void Camera::OnUpdatePosition()
{
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	glm::vec3 cameraPos = transform->GetWorldPosition();
	glm::vec3 targetPos = transform->GetWorldPosition() + transform->forward();
	
	viewMatrix = glm::lookAt(cameraPos, targetPos, transform->up());
}