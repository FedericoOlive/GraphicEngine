#include "FirstPerson.h"

#include <iostream>

#include "GameObjects/Transform.h"
#include <Input/Input.h>

FirstPerson::FirstPerson()
{
	std::function<void(double, double)> onMouseMove = [this](double x, double y) { OnMouseMove(x, y); };
	Input::OnMouseMove.AddListener(onMouseMove);
}
FirstPerson::~FirstPerson(){}

void FirstPerson::OnMouseMove(double x, double y)
{
	glm::vec3 newRot = { y * static_cast<double>(mouseSensitive.x), x * static_cast<double>(mouseSensitive.y), 0 };
	transform->SetRotation(transform->GetRotation() + newRot);
}

void FirstPerson::BindMovements(KeyCode forward, KeyCode left, KeyCode back, KeyCode right, float speed)
{
	this->forward = forward;
	this->left = left;
	this->back = back;
	this->right = right;
	
	speedForward = speed;
	speedLeft = speed;
	speedBack = speed;
	speedRight = speed;
}

void FirstPerson::SetSpeedMovements(float speed)
{
	speedForward = speed;
	speedLeft = speed;
	speedBack = speed;
	speedRight = speed;
}

void FirstPerson::SetSpeedMovements(float speedForward, float speedLeft, float speedBack, float speedRight)
{
	this->speedForward = speedForward;
	this->speedLeft = speedLeft;
	this->speedBack = speedBack;
	this->speedRight = speedRight;
}

void FirstPerson::SetCameraSensitive(float sensitiveX, float sensitiveY)
{
	mouseSensitive = { sensitiveX, sensitiveY };
}

void FirstPerson::Update()
{
	
}

void FirstPerson::Input()
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

void FirstPerson::OnAsigned()
{
	
}
