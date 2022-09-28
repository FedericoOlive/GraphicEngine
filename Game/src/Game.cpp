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
	Texture* texture3 = new Texture("res/sprite3.png");
	sprite3 = CreateSprite(texture3);
	Texture* texture4 = new Texture("res/sprite4.png");
	sprite4 = CreateSprite(texture4);

	sprite->SetColorTint(1, 1, 1);
	sprite2->SetColorTint(1, 1, 1);
	sprite3->SetColorTint(1, 1, 1);
	
}
void Game::Input()
{
	
}

void Game::Update()
{
	indexDraw++;
	
	sprite4->SetColorTint(GetRandom(), GetRandom(), GetRandom());
}

void Game::Draw()
{
	if (indexDraw > 40000)
		indexDraw = 0;
	else if (indexDraw > 25000)
		sprite4->Draw();
	else if (indexDraw > 20000)
		sprite3->Draw();
	else if (indexDraw > 15000)
		sprite2->Draw();
	else if (indexDraw > 10000)
		sprite->Draw();
	else if (indexDraw > 5000)
		quad->Draw();
	else if (indexDraw > 0)
		triangle->Draw();
		
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