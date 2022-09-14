#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	Triangle* triangle;
public:
	void CreateTriangle();
	void Update() override;
};

#endif