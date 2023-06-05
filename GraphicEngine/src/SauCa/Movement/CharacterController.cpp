#include "CharacterController.h"

CharacterController::CharacterController(GameObject* player, GameObject* visualPlayer, GameObject* cameraPivot, GameObject* cameraGameObject, Camera* cameraComponent)
{
	root = player;
	this->visualPlayer = visualPlayer;
	pivot = cameraPivot;
	camera = cameraGameObject;
	this->cameraComponent = cameraComponent;

	root->AddComponent(this);
	visualPlayer->transform->SetParent(root);
	root->transform->SetLocalScale(glm::vec3(1, 1, 1));

	pivot->name = "Camera Pivot";
	pivot->transform->SetLocalPosition({ 0, 1, 0 });
	pivot->transform->SetParent(root);

	camera->name = "Camera Gameplay";
	camera->transform->SetParent(pivot);
	camera->transform->SetLocalPosition({ 0, 1, 3 });
	
	camera->AddComponent(cameraComponent);
	
	movement = new EntityController();
	movement->RemoveRotation(false, true);
	rotation = new EntityController();
	rotation->RemoveMovement();
	rotation->RemoveRotation(true, false);

	root->AddComponent(movement);
	pivot->AddComponent(rotation);
}

CharacterController::~CharacterController()
{
	if (movement == nullptr)
	{
		delete movement;
		movement = nullptr;
	}
	if (rotation == nullptr)
	{
		delete rotation;
		rotation = nullptr;
	}
}

void CharacterController::SetFirstPerson()
{
	
}

void CharacterController::SetThirdPerson()
{
	
}