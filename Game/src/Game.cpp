#include "Game.h"
#include <time.h>

void Game::Initialize()
{
	srand(time(nullptr));

	InitGameSayayin();
	
	gokutext = new Texture("res/goku.png");
	goku = CreateSprite(gokutext);
	goku->SetPosition(1280 / 2, 720 / 2, 0);
	goku->SetScale(50, 50, 50);	

	AddCollision(goku, false);

	tileMap = CreateTileMap("res/TileMap/mymapa.tmx", "res/TileMap/E3.png");
	tileMap->pos = { 640, 300, 0 };
	tileMap->SetSize(2);
}

void Game::InitGameSayayin()
{
	player = new MiniGameSayayin();

	player->ssj1text = new Texture("res/ssj1.png");
	player->ssj2text = new Texture("res/ssj2.png");
	player->ssj3text = new Texture("res/ssj3.png");
	player->godtext = new Texture("res/god.png");

	player->ssj1 = CreateSprite(player->ssj1text);
	player->ssj2 = CreateSprite(player->ssj2text);
	player->ssj3 = CreateSprite(player->ssj3text);
	player->god = CreateSprite(player->godtext);
	
	Material* m = new Material(new Shader(false), false);
	Material* m2 = new Material(new Shader(false), false);
	
	totalKi = CreateQuad(m);
	totalKi->SetColorTint(1, 0.5f, 0, 1);
	totalKi->SetPosition(640, 700, 0);
	totalKi->SetScale(1100, 50, 1);

	actualKi = CreateQuad(m2);
	actualKi->SetColorTint(1, 1, 0, 1);
	actualKi->SetPosition(640, 700, 0);
	actualKi->SetScale(0, 50, 1);
	
	player->CreatePlayerAssets();

	currentForm = 0;
}

void Game::Inputs()
{	
	glm::vec3 pos = goku->GetPosition();
	glm::vec3 rot = goku->GetRotation();
	glm::vec3 scale = goku->GetScale();

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

	if (modified)
	{
		goku->SetPosition(pos);
		goku->SetRotation(rot, false);
		goku->SetScale(scale);
	}

	//std::cout << "Pos: " << player->GetViewportPosition().x << ", " << player->GetViewportPosition().y << ", " << player->GetViewportPosition().z << std::endl;
}

void Game::Update()
{
	ki -= 0.05 * currentForm / 2 * Timer::DeltaTime();

	if (ki < 0)
	{
		ki = 0;
	}
	else if (ki > 1)
	{
		currentForm++;
		chargeable = false;
		ki = 0;
	}

	actualKi->SetScale(ki * 1100, 50, 0);
	UpdateCollisions(tileMap);
}

void Game::Draw()
{
	tileMap->Draw();
	totalKi->Draw();
	actualKi->Draw();
	goku->Draw();
	
	switch (currentForm)
	{
	case 0:
		player->ssj1->Draw(0);
		break;
	case 1:
		player->ssj1->Draw(1);
		if (player->ssj1->GetAnimations()[1]->IsFinished())
		{
			currentForm++;
			chargeable = true;
		}
		break;
	case 2:
		player->ssj1->Draw(2);
		chargeable = true;
		break;
	case 3:
		player->ssj2->Draw(1);
		if (player->ssj2->GetAnimations()[1]->IsFinished())
		{
			currentForm++;
			chargeable = true;
		}
		break;
	case 4:
		player->ssj2->Draw(2);
		chargeable = true;
		break;
	case 5:
		player->ssj3->Draw(1);
		if (player->ssj3->GetAnimations()[1]->IsFinished())
		{
			currentForm++;
			chargeable = true;
		}
		break;
	case 6:
		player->ssj3->Draw(2);
		chargeable = true;
		break;
	case 7:
		player->god->Draw(1);
		if (player->god->GetAnimations()[1]->IsFinished())
		{
			currentForm++;
			chargeable = true;
		}
		break;
	case 8:
		player->god->Draw(2);
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
	delete player;
}