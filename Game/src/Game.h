#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	float multiply = 0.5f;
	Transform* target = nullptr;
	
	GameObject* worldContent = nullptr;
	GameObject* floor = nullptr;
	Sprite* floorSprite = nullptr;
	GameObject* wallRight = nullptr;
	GameObject* wallLeft = nullptr;
	GameObject* wallBack = nullptr;
	GameObject* wallFront = nullptr;
	
	GameObject* player = nullptr;
	GameObject* cameraPivot = nullptr;
	GameObject* camera = nullptr;
	
	GameObject* objectFoward = nullptr;


	GameObject* cubeContent = nullptr;
	GameObject* cube1 = nullptr;
	GameObject* cube2 = nullptr;
	GameObject* cube3 = nullptr;
	GameObject* cube4 = nullptr;


	
	GameObject* goLightDir01 = nullptr;
	GameObject* goLightDir02 = nullptr;
	DirectionalLight* lightDir1 = nullptr;
	DirectionalLight* lightDir2 = nullptr;
	
	GameObject* goLightPoint01	= nullptr;
	GameObject* goLightPoint02	= nullptr;
	GameObject* goLightPoint03	= nullptr;
	GameObject* goLightPoint04	= nullptr;
	PointLight* lightPoint1	= nullptr;
	PointLight* lightPoint2	= nullptr;
	PointLight* lightPoint3	= nullptr;
	PointLight* lightPoint4	= nullptr;

	GameObject* goLightSpot01 = nullptr;
	GameObject* goLightSpot02 = nullptr;
	SpotLight* lightSpot1 = nullptr;
	SpotLight* lightSpot2 = nullptr;
	
	GameObject* goLightPointArround01 = nullptr;
	GameObject* goLightPointArround02 = nullptr;
	GameObject* goLightPointArround03 = nullptr;
	GameObject* goLightPointArround04 = nullptr;
	PointLight* lightPointArround = nullptr;


	GameObject* goLightPointStatic01 = nullptr;
	GameObject* goLightPointStatic02 = nullptr;
	GameObject* goLightPointStatic03 = nullptr;
	
	GameObject* cameraMinimapGo = nullptr;
	Camera* cameraMinimap;

public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void DeInitialize() override;
	void Draw();

	void SetLights();
	void SetEnviroment();
	void AddListeners();

	
};

#endif