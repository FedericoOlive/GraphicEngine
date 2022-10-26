#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	srand(time(nullptr));
	triangle = CreateTriangle();
	quad = CreateQuad();

	/*triangle->SetColorTint(1, 0, 0, 0.2f);
	triangle->SetPosition(0.7f, 0.7f, 0.0f);
	triangle->SetScale(0.3f, 0.3f, 0.0f);

	quad->SetColorTint(0, 1, 1, 0.1f);
	quad->SetPosition(-0.7f, 0.7f, 0.0f);
	quad->SetScale(0.3f, 0.3f, 0.0f);*/

	Texture* texture = new Texture("res/sprite1.png");
	sprite1 = CreateSprite(texture);
	Texture* texture2 = new Texture("res/sprite2.png");
	sprite2 = CreateSprite(texture2);
	Texture* texture3 = new Texture("res/sprite3.png");
	sprite3 = CreateSprite(texture3);
	
	Texture* backg = new Texture("res/Tile.png");
	backGround = CreateSprite(backg);
	
	backGround->SetColorTint(1, 1, 1, 1);
	backGround->SetPosition(0,0,0);
	backGround->SetScale(1,1,1);
	//backGround->SetPosition(0.5f, 0.5f, 0.5f);
	
	/*sprite1->SetColorTint(1, 1, 1, 0.3f);
	sprite1->SetPosition(-0.7f, -0.7f, 0.0f);
	sprite1->SetScale(0.5f, 0.5f, 0.0f);*/

	sprite2->SetColorTint(1, 1, 1, 1);
	sprite2->SetPosition(0.0f, 0.0f, 0.0f);
	sprite2->SetScale(1, 1, 1);

	/*sprite3->SetColorTint(0, 0, 1, 0.5f);
	sprite3->SetPosition(0.0f, 0.05f, 0.0f);
	sprite3->SetScale(1.0f, 1.0f, 0.0f);*/
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
	/*
	cout << "\nDelta Time: " << DeltaTime();
	cout << "\nElaps Time: " << ElapsedTime();
	cout << "\n----------------------------------------";
	*/
	//sprite3->SetColorTint(GetRandom(), GetRandom(), GetRandom(), 1);
	/*sprite1->SetRotation(0, 0, indexDraw / 90, true);
	triangle->SetRotation(0, 0, indexDraw / 90, true);
	quad->SetRotation(0, 0, -indexDraw / 90, true);*/
}

void Game::Draw()
{
	backGround->Draw();
	sprite2->Draw();
	/*sprite3->Draw();
	sprite1->Draw();
	quad->Draw();
	triangle->Draw();*/
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