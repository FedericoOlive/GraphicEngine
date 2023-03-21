#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	GameObject* target = nullptr;
	GameObject* player = nullptr;
	GameObject* floor = nullptr;
	GameObject* camera = nullptr;
	Camera* cam = nullptr;
	float multiply = 2;

public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void Draw();
	void DeInitialize() override;
};

#endif