#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	Quad* floor;
	Sprite* player;
	Texture* text;
	int currentAnim;
	int indexDraw = 0;
	float multiply = 1;
public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void Draw()override;
	void DeInitialize() override;
	float GetRandom();
};

#endif