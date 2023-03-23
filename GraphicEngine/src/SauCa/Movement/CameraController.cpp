#include "CameraController.h"

#include <iostream>

#include "GameObjects/Transform.h"
#include <Input/Input.h>

CameraController::CameraController(Camera* camera)
{
	this->camera = camera;
	std::function<void(double, double)> onMouseMove = [this](double x, double y) { OnMouseMove(x, y); };
	Input::OnMouseMove.AddListener(onMouseMove);
}

CameraController::~CameraController()
{
	
}

void CameraController::OnMouseMove(double x, double y)
{
	glm::vec3 newRot = { y * static_cast<double>(mouseSensitive.x), x * static_cast<double>(mouseSensitive.y), 0 };
	transform->SetRotation(transform->GetRotation() + newRot);
	
}

void CameraController::SetTarget(GameObject* target)
{
	this->target = target;
	camera->target = target;
}
void CameraController::SetOffset(glm::vec3 offset)
{
	this->offset = offset;
	camera->offsetViewport = offset;
	camera->target = target;
}

void CameraController::SetFirstPersonDefault()
{
	BindMovements(KeyCode::W, KeyCode::A, KeyCode::S, KeyCode::D, 1.0f);
	SetCameraSensitive(0.5f, 0.5f);
	
	SetTarget(nullptr);
	SetOffset({ 0, 0, 0 });
}

void CameraController::SetThirdPersonDefault()
{
	BindMovements(KeyCode::W, KeyCode::A, KeyCode::S, KeyCode::D, 10.0f);
	SetCameraSensitive(0.5f, 0.5f);
	
	SetTarget(gameobject);
	SetOffset({ 0, 200, -200 });
}

void CameraController::BindMovements(KeyCode forward, KeyCode left, KeyCode back, KeyCode right, float speed)
{
	this->forward = forward;
	this->left = left;
	this->back = back;
	this->right = right;
	
	SetSpeedMovements(speed);
}

void CameraController::SetSpeedMovements(float speed)
{
	speedForward = speed;
	speedLeft = speed;
	speedBack = speed;
	speedRight = speed;
}

void CameraController::SetSpeedMovements(float speedForward, float speedLeft, float speedBack, float speedRight)
{
	this->speedForward = speedForward;
	this->speedLeft = speedLeft;
	this->speedBack = speedBack;
	this->speedRight = speedRight;
}

void CameraController::SetCameraSensitive(float sensitiveX, float sensitiveY)
{
	mouseSensitive = { sensitiveX, sensitiveY };
}

void CameraController::Update()
{
	
}

void CameraController::Input()
{
	if (transform == nullptr)
		return;

	glm::vec3 direction = { 0.0f, 0.0f, 0.0f };

	if (Input::IsKeyDown(forward)) { direction = transform->forward * speedForward; }
	if (Input::IsKeyDown(left)) { direction = -transform->right * speedLeft; }
	if (Input::IsKeyDown(back)) { direction = -transform->forward * speedBack; }
	if (Input::IsKeyDown(right)) { direction = transform->right * speedRight; }

	direction.y = 0.0f;
	//direction = glm::normalize(direction);
	
	transform->SetWorldPosition(direction + transform->GetWorldPosition());
}

void CameraController::OnAsigned()
{
	
}
