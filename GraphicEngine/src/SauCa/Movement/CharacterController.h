#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H
#include "EntityController.h"
#include "GameObjects/GameObject.h"

class CharacterController : public Component
{
private:
	Camera* cameraComponent = nullptr;
public:
	EntityController* movement = nullptr;
	EntityController* rotation = nullptr;
	
	GameObject* root = nullptr;
	GameObject* visualPlayer = nullptr;
	GameObject* pivot = nullptr;
	GameObject* camera = nullptr;
	Camera* GetCamera() { return cameraComponent; }
	CharacterController(GameObject* player, GameObject* visualPlayer, GameObject* cameraPivot, GameObject* cameraGameObject, Camera* cameraComponent);
	~CharacterController() override;
	void SetFirstPerson();
	void SetThirdPerson();
};
#endif