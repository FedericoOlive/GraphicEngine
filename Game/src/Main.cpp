#include "SauCa.h"
#include "Game.h"

void main()
{
	Game* game= new Game();
	game->Init();
	delete game;
}