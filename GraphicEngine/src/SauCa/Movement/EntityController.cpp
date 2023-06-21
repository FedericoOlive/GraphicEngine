#include "EntityController.h"

#include <iostream>

#include "GameObjects/Transform.h"
#include <Input/Input.h>

EntityController::EntityController()
{
	name = "EntityController";
	std::function<void(double, double)> onMouseMove = [this](double x, double y) { OnMouseMove(x, y); };
	Input::OnMouseMove.AddListener(onMouseMove);
}

EntityController::~EntityController()
{
	
}

void EntityController::OnMouseMove(double x, double y)
{
	if (lockDirectionByLockCursor)
	{
		if (!Input::IsMouseButtonHolding(MouseCode::MouseRight))
		{
			if (Window::IsLockedCursor())
			{
				Window::LockCursor(false);
			}
			return;
		}

		if (!Window::IsLockedCursor())
		{
			Window::LockCursor(true);
		}
	}
	
	glm::vec3 rotation = transform->GetLocalRotation();

	if (rotateX)
		rotation.x -= y * static_cast<double>(mouseSensitive.y);
	if (rotateY)
		rotation.y -= x * static_cast<double>(mouseSensitive.x);

	if (rotateX || rotateY)
	{
		if (rotation.x > maxVerticalAngle)
			rotation.x = maxVerticalAngle;
		else if (rotation.x < minVerticalAngle)
			rotation.x = minVerticalAngle;
		transform->SetLocalRotation(rotation);
	}
}

void EntityController::RemoveMovement(bool foward, bool left, bool back, bool right)
{
	if (foward) this->forward = KeyCode::None;
	if (left) this->left = KeyCode::None;
	if (back) this->back = KeyCode::None;
	if (right) this->right = KeyCode::None;
}

void EntityController::RemoveRotation(bool xAxis, bool yAxis)
{
	rotateX = !xAxis;
	rotateY = !yAxis;
}



void EntityController::BindMovements(KeyCode forward, KeyCode left, KeyCode back, KeyCode right, float speed)
{
	this->forward = forward;
	this->left = left;
	this->back = back;
	this->right = right;
	
	SetSpeedMovements(speed);
}

void EntityController::SetSpeedMovements(float speed)
{
	speedForward = speed;
	speedLeft = speed;
	speedBack = speed;
	speedRight = speed;
}

void EntityController::SetSpeedMovements(float speedForward, float speedLeft, float speedBack, float speedRight)
{
	this->speedForward = speedForward;
	this->speedLeft = speedLeft;
	this->speedBack = speedBack;
	this->speedRight = speedRight;
}

void EntityController::SetCameraSensitive(float sensitiveX, float sensitiveY)
{
	mouseSensitive = { sensitiveX, sensitiveY };
}

void EntityController::Update(double deltaTime)
{
	
}

void EntityController::Input()
{
	if (transform == nullptr)
		return;
	
	direction = { 0.0f, 0.0f, 0.0f };
	bool hasMoved = false;

	bool isGoingForward = Input::IsKeyHolding(forward);
	bool isGoingBack = Input::IsKeyHolding(back);
	bool isGoingRight = Input::IsKeyHolding(right);
	bool isGoingLeft = Input::IsKeyHolding(left);
		
	if (isGoingForward && !isGoingBack)
	{
		hasMoved = true;
		direction += transform->forward() * speedForward;
	}
	if (isGoingBack && !isGoingForward)
	{
		hasMoved = true;
		direction += -transform->forward() * speedBack;
	}
	if (isGoingRight && !isGoingLeft)
	{
		hasMoved = true;
		direction += transform->right() * speedRight;
	}
	if (isGoingLeft && !isGoingRight)
	{
		hasMoved = true;
		direction += -transform->right() * speedLeft;
	}

	direction = glm::normalize(direction);

	if (hasMoved)
		transform->SetLocalPosition(transform->GetLocalPosition() + direction);
}

void EntityController::OnAsigned()
{
	
}