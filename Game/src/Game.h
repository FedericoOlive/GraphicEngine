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
	GameObject* cube1 = nullptr;
	GameObject* cube2 = nullptr;
	GameObject* cube3 = nullptr;
	GameObject* objectFoward = nullptr;

	GameObject* cubeContent = nullptr;
	
	GameObject* goLightPointArround01 = nullptr;
	GameObject* goLightPointArround02 = nullptr;
	GameObject* goLightPointArround03 = nullptr;
	GameObject* goLightPointArround04 = nullptr;

	float* targetFloatModify = nullptr;
	string targetString = "";
	SpotLight* spotlightPlayer = nullptr;
	int currentColor = 0;
	glm::vec3 playerZoom = {0, 1, 3};

public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void DeInitialize() override;
	void Draw() override;

	void SetLights();
	void SetEnviroment();
	void AddListeners();
	void AddPlayer();
	void AddMinimap();
	void AddModels3D();

	void ChangeColorSpotLight();
	void OnMouseMove(double xPos, double yPos);
	void OnMouseScrollMovement(double xOffset, double yOffset);

};

#endif