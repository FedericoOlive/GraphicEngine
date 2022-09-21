#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	Triangle* triangle;
public:
	void Initialize()override;
	void Input() override;
	void Update()override;
	void Draw()override;
	void DeInitialize() override;
};

#endif