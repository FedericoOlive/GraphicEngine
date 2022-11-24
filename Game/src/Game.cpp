#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	srand(time(nullptr));

	Texture* texture = new Texture("res/vegito.png");
	sprite1 = CreateSprite(texture);

	sprite1->SetColorTint(1, 1, 1, 1);
	sprite1->SetPosition(1, 0.0f, 0.0f);
	sprite1->SetScale(1, 1, 1);

	Texture* texture2 = new Texture("res/sprite2.png");
	sprite2 = CreateSprite(texture2);
	
	sprite2->SetColorTint(1, 1, 1, 1);
	sprite2->SetPosition(-1, 0.0f, 0.0f);
	sprite2->SetScale(1, 1, 1);

	Texture* texture3 = new Texture("res/vegito2.png");
	sprite3 = CreateSprite(texture3);

	sprite3->SetColorTint(1, 1, 1, 1);
	sprite3->SetPosition(0.0f, 0.8f, 0.0f);
	sprite3->SetScale(1, 1, 1);

	Texture* texture4 = new Texture("res/god.png");
	sprite4 = CreateSprite(texture4);

	sprite4->SetColorTint(1, 1, 1, 1);
	sprite4->SetPosition(0.0f, -0.8f, 0.0f);
	sprite4->SetScale(1, 1, 1);


	sprite1->AddAnimation(0, 0, 384, 384, 7296, 384, 2.5f, 19);
	
	sprite2->AddAnimation(0, 0, 309, 309, 1854, 309, 0.2f,6);	

	sprite3->AddAnimation(0, 0, 498, 357, 8466, 357, 0.5f, 17);

	sprite4->AddAnimation(0, 0, 500, 281, 5000, 281, 0.5f, 10);
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

	std::cout << "Pos: " << sprite2->GetViewportPosition().x << ", " << sprite2->GetViewportPosition().y << ", " << sprite2->GetViewportPosition().z << std::endl;
}

void Game::Update()
{
	indexDraw++;
}

void Game::Draw()
{
	sprite1->Draw();
	sprite2->Draw();
	sprite3->Draw();
	sprite4->Draw();
}

float Game::GetRandom()
{
	int random = rand() % 100;
	float max = 100;
	return random / max;
}

void Game::DeInitialize()
{
	sprite2->DeleteTextureAsociate();
	sprite3->DeleteTextureAsociate();
	sprite1->DeleteTextureAsociate();
	sprite4->DeleteTextureAsociate();
	delete sprite1;
	delete sprite2;
	delete sprite3;
	delete sprite4;
	delete triangle;
	delete quad;
	delete backGround;
}