#include "CharacterController.h"

#include <iostream>

#include "GameObjects/Transform.h"
#include <Input/Input.h>

CharacterController::CharacterController()
{
	name = "CharacterController";
	std::function<void(double, double)> onMouseMove = [this](double x, double y) { OnMouseMove(x, y); };
	Input::OnMouseMove.AddListener(onMouseMove);
}

CharacterController::~CharacterController()
{
	
}

void CharacterController::OnMouseMove(double x, double y)
{
	glm::vec3 newRot = transform->GetLocalRotation();

	if (rotateX)
		newRot.x -= y * static_cast<double>(mouseSensitive.y);
	if (rotateY)
		newRot.y -= x * static_cast<double>(mouseSensitive.x);

	if (rotateX || rotateY)
		transform->SetLocalRotation(newRot);
}

void CharacterController::RemoveMovement(bool foward, bool left, bool back, bool right)
{
	if (foward) this->forward = KeyCode::None;
	if (left) this->left = KeyCode::None;
	if (back) this->back = KeyCode::None;
	if (right) this->right = KeyCode::None;
}

void CharacterController::RemoveRotation(bool xAxis, bool yAxis)
{
	rotateX = xAxis;
	rotateY = yAxis;
}

void CharacterController::BindMovements(KeyCode forward, KeyCode left, KeyCode back, KeyCode right, float speed)
{
	this->forward = forward;
	this->left = left;
	this->back = back;
	this->right = right;
	
	SetSpeedMovements(speed);
}

void CharacterController::SetSpeedMovements(float speed)
{
	speedForward = speed;
	speedLeft = speed;
	speedBack = speed;
	speedRight = speed;
}

void CharacterController::SetSpeedMovements(float speedForward, float speedLeft, float speedBack, float speedRight)
{
	this->speedForward = speedForward;
	this->speedLeft = speedLeft;
	this->speedBack = speedBack;
	this->speedRight = speedRight;
}

void CharacterController::SetCameraSensitive(float sensitiveX, float sensitiveY)
{
	mouseSensitive = { sensitiveX, sensitiveY };
}

void CharacterController::Update()
{
	
}

void CharacterController::Input()
{
	if (transform == nullptr)
		return;

	glm::vec3 direction = { 0.0f, 0.0f, 0.0f };
	bool hasMoved = false;
	if (Input::IsKeyDown(forward))
	{
		hasMoved = true;
		direction = transform->forward() * speedForward;
	}
	if (Input::IsKeyDown(left))
	{
		hasMoved = true;
		direction = -transform->right() * speedLeft;
	}
	if (Input::IsKeyDown(back))
	{
		hasMoved = true;
		direction = -transform->forward() * speedBack;
	}
	if (Input::IsKeyDown(right))
	{
		hasMoved = true;
		direction = transform->right() * speedRight;
	}

	//direction.y = 0.0f;

	if (hasMoved)
		transform->SetLocalPosition(transform->GetLocalPosition() + direction);
}

void CharacterController::OnAsigned()
{
	
}