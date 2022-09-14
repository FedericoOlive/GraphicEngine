#include "SauCa.h"

void main()
{
	BaseGame* baseGame = new BaseGame();
	baseGame->Init();
	Triangle* triangle = new Triangle();
	baseGame->Draw(triangle);
	delete baseGame;
}

