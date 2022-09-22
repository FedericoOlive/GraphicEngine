#include "Game.h"
#include <time.h>

void Game::Initialize()
{
	srand(time(nullptr));
	triangle = CreateTriangle();
	quad = CreateQuad();
	
	Texture* texture = new Texture("res/sprite1.png");
	sprite = CreateSprite(texture);
	Texture* texture2 = new Texture("res/sprite2.png");
	sprite2 = CreateSprite(texture2);
	
}
void Game::Input()
{
	
}

void Game::Update()
{
	indexDraw++;
	
	sprite->SetColorTint(GetRandom(), GetRandom(), GetRandom());
	sprite2->SetColorTint(GetRandom(), GetRandom(), GetRandom());
}

void Game::Draw()
{
	if (indexDraw > 200)
		indexDraw = 0;
	else if (indexDraw > 150)
		triangle->Draw();
	else if (indexDraw > 100)
		sprite2->Draw();
	else if (indexDraw > 50)
		quad->Draw();
	else if (indexDraw > 0)
		sprite->Draw();
}
float Game::GetRandom()
{
	int random = rand() % 100;
	float max = 100;
	return random / max;
}
void Game::DeInitialize()
{
	delete triangle;
	delete quad;
	delete sprite;
	delete sprite2;
}