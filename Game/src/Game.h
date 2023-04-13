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

public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void DeInitialize() override;
	void Draw();

	void SetEnviroment();
	void AddListeners();
};

#endif