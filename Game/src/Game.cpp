#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	srand(time(nullptr));

	Texture* texture2 = new Texture("res/sprite2.png");
	sprite2 = CreateSprite(texture2);
	
	sprite2->SetColorTint(1, 1, 1, 1);
	sprite2->SetPosition(0.0f, 0.0f, 0.0f);
	sprite2->SetScale(1, 1, 1);

	sprite2->AddAnimation(0, 0, 309, 309, 1854, 309, 0.3f,6);
}

void Game::Inputs()
{
	glm::vec3 pos = sprite2->GetPosition();
	glm::vec3 rot = sprite2->GetRotation();
	glm::vec3 scale = sprite2->GetScale();

	bool modified = false;

	if(IsKeyDown(KeyCode::W))
	{
		modified = true;
		pos.y += 0.001f;
	}

	if (IsKeyDown(KeyCode::A))
	{
		modified = true;
		pos.x -= 0.001f;
	}
		
	if (IsKeyDown(KeyCode::S))
	{
		modified = true;
		pos.y -= 0.001f;
	}
		
	if (IsKeyDown(KeyCode::D))
	{
		modified = true;
		pos.x += 0.001f;
	}
		

	if (IsKeyReleased(KeyCode::Q))
	{
		modified = true;
		rot.z += 15;
	}
		
	if (IsKeyReleased(KeyCode::E))
	{
		modified = true;
		rot.z -= 15;
	}

	if (IsKeyPressed(KeyCode::Z))
	{
		modified = true;
		scale.x += 0.1f;
		scale.y += 0.1f;
		scale.z = 0;
	}
	if (IsKeyPressed(KeyCode::X))
	{
		modified = true;
		scale.x -= 0.1f;
		scale.y -= 0.1f;
		scale.z = 0;
	}

	if (modified) 
	{
		sprite2->SetPosition(pos);
		sprite2->SetScale(scale);
		sprite2->SetRotation(rot, false);
	}
}

void Game::Update()
{
	indexDraw++;
}

void Game::Draw()
{
	sprite2->Draw();
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
	delete sprite1;
	delete sprite2;
	delete sprite3;
	delete backGround;
}