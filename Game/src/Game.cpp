#include "Game.h"
void Game::CreateTriangle()
{
	triangle = new Triangle();
}

void Game::Update()
{
	Draw(triangle);
}