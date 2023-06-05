#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	float multiply = 0.5f;
	Transform* target = nullptr;
	Camera* camera = nullptr;
	CharacterController* player = nullptr;
	
	GameObject* objectFoward = nullptr;

	GameObject* cubeContent = nullptr;
	
	GameObject* goLightPointArround01 = nullptr;
	GameObject* goLightPointArround02 = nullptr;
	GameObject* goLightPointArround03 = nullptr;
	GameObject* goLightPointArround04 = nullptr;

public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void DeInitialize() override;
	void Draw();

	void SetLights();
	void SetEnviroment();
	void AddListeners();
	void AddPlayer();
	void AddMinimap();
	void AddModels3D();

	void OnMouseMove(double xPos, double yPos);
	void OnMouseScrollMovement(double xOffset, double yOffset);

};

#endif