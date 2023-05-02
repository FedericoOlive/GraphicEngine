#include "Game.h"

void main()
{
	srand(time(nullptr));
	
	Game* game= new Game();
	game->Init();
	delete game;
}