#include "Camera.h"
#include "Renderer.h"
#include "GameObjects/GameObject.h"

Camera::Camera(glm::vec2 viewportPosition, glm::vec2 viewportSize, CameraType cameraType)
{
	name = "Camera";
	aspect = viewportSize.x / viewportSize.y;
	this->viewportPosition = viewportPosition;
	this->viewportSize = viewportSize;
	this->cameraType = cameraType;
	glViewport((GLint)viewportPosition.x, (GLint)viewportPosition.y, (GLint)viewportSize.x, (GLint)viewportSize.y);

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
}

Camera::~Camera()
{
	Renderer::RemoveCamera(this);
}

void Camera::BeginDraw()
{
	glViewport((GLint)viewportPosition.x, (GLint)viewportPosition.y, (GLint)viewportSize.x, (GLint)viewportSize.y);
}

void Camera::SetCameraOrthogonal(float near, float far)
{
	projectionMatrix = glm::ortho(0.0f, viewportSize.x / cameraZoom, 0.0f, viewportSize.y / cameraZoom, near, far);
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

void Camera::SetZoom(float cameraZoom)
{
	this->cameraZoom = cameraZoom;
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
}

void Camera::SetCameraType(CameraType cameraType)
{
	this->cameraType = cameraType;

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
}
