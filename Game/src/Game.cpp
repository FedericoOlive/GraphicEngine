#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	srand(time(nullptr));

	floor = CreateQuad();
	floor->SetColorTint(1, 1, 1, 1);
	floor->SetPosition(640, 0, 0);
	floor->SetScale(1280, 100, 1);
	AddCollision(floor, true);

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

	player = new Player();

	player->ssj1text = new Texture("res/ssj1.png");
	player->ssj2text = new Texture("res/ssj2.png");
	player->ssj3text = new Texture("res/ssj3.png");
	player->godtext = new Texture("res/god.png");

	player->ssj1 = CreateSprite(player->ssj1text);
	player->ssj2 = CreateSprite(player->ssj2text);
	player->ssj3 = CreateSprite(player->ssj3text);
	player->god = CreateSprite(player->godtext);

	player->CreatePlayerAssets();

	AddCollision(player->ssj1, false);

	currentForm = 0;

	tileMap = CreateTileMap("res/TileMap/mymapa.tmx", "res/TileMap/E3.png");
	tileMap->pos = { 1280 / 2, 720 / 2, 0 };
	tileMap->SetSize(3.0f);
}

void Game::Inputs()
{
	
	glm::vec3 pos = player->position;
	glm::vec3 rot = player->rotation;
	glm::vec3 scale = player->scale;
	cout << "Player Pos: X: " << pos.x << " Y: " << pos.y << " Z:" << pos.z << " \n";
	cout << "Player Pos: X: " << player->ssj1->GetPosition().x << " Y: " << player->ssj1->GetPosition().y << " Z:" << player->ssj1->GetPosition().z << " \n";
	//cout << "Player Rot: X: " << rot.x << " Y: " << rot.y << " Z:" << rot.z << " \n";
	//cout << "Player Scale: X: " << scale.x << " Y: " << scale.y << " Z:" << scale.z << " \n";
	cout << "-----------------------------------------------\n";

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
		player->Move(pos);
		player->SetScale(scale);
		player->SetRotation(rot);
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

	actualKi->SetScale(ki * 1000, 180, 0);
	UpdateCollisions(tileMap);

	player->position = player->ssj1->GetPosition();
}

void Game::Draw()
{
	tileMap->Draw();
	//floor->Draw();
	//totalKi->Draw();
	//actualKi->Draw();

	player->ssj1->Draw(0);
	
	/*switch (currentForm)
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
	}*/
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