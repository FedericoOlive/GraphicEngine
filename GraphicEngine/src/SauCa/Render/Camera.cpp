#include "Camera.h"
#include "Renderer.h"
#include "GameObjects/GameObject.h"

Camera::Camera(glm::vec2 viewportPosition, glm::vec2 viewportSize, CameraType cameraType)
{
	name = "Camera";
	aspect = viewportSize.x / viewportSize.y;
	this->fov = 45.0f;
	this->near = 0.1f;
	this->far = 1000.0f;
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
	
	frustum = new Frustum();
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
	this->near = near;
	this->far = far;
	projectionMatrix = glm::ortho(0.0f, viewportSize.x / cameraZoom, 0.0f, viewportSize.y / cameraZoom, near, far);
}

void Camera::SetCameraPerspective(float fov, float near, float far)
{
	this->fov = fov;
	this->near = near;
	this->far = far;
	projectionMatrix = glm::perspective(glm::radians(fov * cameraZoom), aspect, near, far);
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

void Camera::SetFov(float fov)
{
	this->fov = fov;
	SetZoom(cameraZoom, fov);
}

void Camera::SetZoom(float cameraZoom, float fov)
{
	this->cameraZoom = cameraZoom;
	this->fov = fov;
	switch (cameraType)
	{
	case Perspective:
		SetCameraPerspective();
		break;
	case Orthogonal:
		SetCameraOrthogonal();
		break;
	default:
		SetCameraPerspective(fov);
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

void Camera::AddToRenderList(GameObject* gameObject)
{
	cameraRenderList.remove(gameObject);
	cameraRenderList.push_back(gameObject);
}

void Camera::DrawRenderList(Frustum* frustum)
{
	//UpdateFrustum();

	BeginDraw();
	for (auto iter = cameraRenderList.begin(); iter != cameraRenderList.end(); ++iter)
	{
		if ((*iter)->transform->parent == nullptr)
			(*iter)->Draw(this, frustum);
	}
}

void Camera::UpdateFrustum()
{
	frustum->Update(fov, aspect, far, near, transform->GetWorldPosition(), transform->forward(), transform->right(), transform->up());
}