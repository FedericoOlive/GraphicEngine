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

	Material* m = new Material(new Shader(false), false);
	Material* m2 = new Material(new Shader(false), false);

	totalKi = CreateQuad(m);
	totalKi->SetColorTint(1, 0.5f, 0, 1);
	totalKi->SetPosition(640, 600, 0);
	totalKi->SetScale(1100, 200, 1);

	actualKi = CreateQuad(m2);
	actualKi->SetColorTint(1, 1, 0, 1);
	actualKi->SetPosition(640, 600, 0);
	actualKi->SetScale(0, 180, 1);

	ssj1text = new Texture("res/ssj1.png");

	
	ssj1 = CreateSprite(ssj1text);
	ssj1->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
	ssj1->SetPosition(640, 360, 0);
	ssj1->SetScale(400, 400, 1);
	ssj1->AddCollision();
	ssj1->AddAnimation(0, 0, 410, 410, 6150, 410, 1);
	ssj1->AddAnimation(0, 0, 410, 410, 6150, 410, 2, 13);
	ssj1->AddAnimation(11, 0, 410, 410, 6150, 410, 1);

	ssj2text = new Texture("res/ssj2.png");


	ssj2 = CreateSprite(ssj2text);
	ssj2->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
	ssj2->SetPosition(640, 360, 0);
	ssj2->SetScale(400, 400, 1);
	ssj2->AddCollision();
	ssj2->AddAnimation(0, 0, 410, 410, 6970, 410, 1);
	ssj2->AddAnimation(0, 0, 410, 410, 6970, 410, 3, 17);
	ssj2->AddAnimation(16, 0, 410, 410, 6970, 410, 1);

	ssj3text = new Texture("res/ssj3.png");


	ssj3 = CreateSprite(ssj3text);
	ssj3->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
	ssj3->SetPosition(640, 360, 0);
	ssj3->SetScale(400, 400, 1);
	ssj3->AddCollision();
	ssj3->AddAnimation(0, 0, 410, 410, 10660, 410, 1);
	ssj3->AddAnimation(0, 0, 410, 410, 10660, 410, 3.2, 22);
	ssj3->AddAnimation(21, 0, 410, 410, 10660, 410, 1);

	godtext = new Texture("res/god.png");


	god = CreateSprite(godtext);
	god->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
	god->SetPosition(640, 360, 0);
	god->SetScale(400, 400, 1);
	god->AddCollision();
	god->AddAnimation(0, 0, 410, 410, 13120, 410, 1);
	god->AddAnimation(0, 0, 410, 410, 13120, 410, 3.2, 28);
	god->AddAnimation(28, 0, 410, 410, 13120, 410, 1);

	currentForm = 0;
}

void Game::Inputs()
{
	/*glm::vec3 pos = player->GetPosition();
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
	}*/
	
	if (IsKeyPressed(KeyCode::F) && chargeable)
	{
		ki += 0.05f;
		cout << ki << endl;
	}

	if (IsKeyDown(KeyCode::R))
	{
		ki = 0;
		currentForm = 0;
		currentAnim = 0;
	}

	/*if (modified)
	{
		player->Move(pos);
		player->SetScale(scale);
		player->SetRotation(rot, false);
	}*/

	//std::cout << "Pos: " << player->GetViewportPosition().x << ", " << player->GetViewportPosition().y << ", " << player->GetViewportPosition().z << std::endl;
}

void Game::Update()
{
	ki -= 0.05 * currentForm/2 * Timer::DeltaTime();
	if (ki < 0) 
	{
		ki = 0;
	}
	if (ki > 1) 
	{
		currentForm++;
		chargeable = false;
		ki = 0;
	}
	actualKi->SetScale(ki * 1000, 180, 0);
}

void Game::Draw()
{
	floor->Draw();
	totalKi->Draw();
	actualKi->Draw();
	switch (currentForm)
	{
		case 0:
			ssj1->Draw(0);
			break;
		case 1:
			ssj1->Draw(1);
			if (ssj1->GetAnimations()[1]->IsFinished()) 
			{
				currentForm++;
				chargeable = true;
			}
			break;
		case 2:
			ssj1->Draw(2);
			chargeable = true;
			break;
		case 3:
			ssj2->Draw(1);
			if (ssj2->GetAnimations()[1]->IsFinished())
			{
				currentForm++;
				chargeable = true;
			}
			break;
		case 4:
			ssj2->Draw(2);
			chargeable = true;
			break;
		case 5:
			ssj3->Draw(1);
			if (ssj3->GetAnimations()[1]->IsFinished())
			{
				currentForm++;
				chargeable = true;
			}
			break;
		case 6:
			ssj3->Draw(2);
			chargeable = true;
			break;
		case 7:
			god->Draw(1);
			if (god->GetAnimations()[1]->IsFinished())
			{
				currentForm++;
				chargeable = true;
			}
			break;
		case 8:
			god->Draw(2);
			chargeable = false;
			break;
		default:
			break;
	}
	
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
	delete ssj1;
}