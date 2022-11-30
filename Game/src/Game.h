#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	Quad* floor;
	Quad* totalKi;
	Quad* actualKi;
	Sprite* ssj1;
	Sprite* ssj2;
	Sprite* ssj3;
	Sprite* god;
	Texture* ssj1text;
	Texture* ssj2text;
	Texture* ssj3text;
	Texture* godtext;
	int currentForm;
	int currentAnim;
	float ki = 0;
	bool chargeable = true;
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