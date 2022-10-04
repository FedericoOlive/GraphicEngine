#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	Triangle* triangle;
	Quad* quad;
	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	int indexDraw = 0;
public:
	void Initialize()override;
	void Input() override;
	void Update()override;
	void Draw()override;
	void DeInitialize() override;
	float GetRandom();
};

#endif