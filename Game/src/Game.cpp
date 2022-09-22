#include "Game.h"

void Game::Initialize()
{
	triangle = CreateTriangle();
	Texture* texture = new Texture("res/ELsprite.png");
	sprite = CreateSprite(texture);
}
void Game::Input()
{
	
}

void Game::Draw()
{
	sprite->Draw();
	triangle->Draw();
}

void Game::DeInitialize()
{
	delete triangle;
	delete sprite;
}

void Game::Update()
{
	
}