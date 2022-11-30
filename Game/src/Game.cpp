#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	srand(time(nullptr));

	floor = CreateQuad();
	floor->SetColorTint(1, 1, 1, 1);
	floor->SetPosition(640, 0, 0);
	floor->SetScale(1280, 100, 1);
	floor->AddCollision();

	text = new Texture("res/gokucharge.png");

	
	player = CreateSprite(text);
	player->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
	player->SetPosition(640, 360, 0);
	player->SetScale(400, 400, 1);
	player->AddCollision();
	player->AddAnimation(0, 0, 221, 219, 7514, 219, 0.7, 2);
	player->AddAnimation(442, 0, 221, 219, 7514, 219, 0.7, 8);
}

void Game::Inputs()
{
	glm::vec3 pos = player->GetPosition();
	glm::vec3 rot = player->GetRotation();
	glm::vec3 scale = player->GetScale();

	bool modified = false;

	if(IsKeyDown(KeyCode::W))
	{
		modified = true;
		pos.y += 1 * multiply;
	}

	if (IsKeyDown(KeyCode::A))
	{
		modified = true;
		pos.x -= 1 * multiply;
	}
		
	if (IsKeyDown(KeyCode::S))
	{
		modified = true;
		pos.y -= 1 * multiply;
	}
		
	if (IsKeyDown(KeyCode::D))
	{
		modified = true;
		pos.x += 1 * multiply;
	}
		

	if (IsKeyDown(KeyCode::Q))
	{
		modified = true;
		rot.z += 1 * multiply;
	}
		
	if (IsKeyDown(KeyCode::E))
	{
		modified = true;
		rot.z -= 1 * multiply;
	}

	if (IsKeyDown(KeyCode::Z))
	{
		modified = true;
		scale.x += 1 * multiply;
		scale.y += 1 * multiply;
		scale.z = 0 * multiply;
	}
	if (IsKeyDown(KeyCode::X))
	{
		modified = true;
		scale.x -= 1 * multiply;
		scale.y -= 1 * multiply;
		scale.z = 0 * multiply;
	}
	currentAnim = 0;
	if (IsKeyDown(KeyCode::F))
	{
		currentAnim = 1;
	}

	if (modified)
	{
		player->Move(pos);
		player->SetScale(scale);
		player->SetRotation(rot, false);
	}

	std::cout << "Pos: " << player->GetViewportPosition().x << ", " << player->GetViewportPosition().y << ", " << player->GetViewportPosition().z << std::endl;
}

void Game::Update()
{
	indexDraw++;
}

void Game::Draw()
{
	floor->Draw();
	player->Draw(currentAnim);
}

float Game::GetRandom()
{
	int random = rand() % 100;
	float max = 100;
	return random / max;
}

void Game::DeInitialize()
{
	delete floor;
	delete player;
}