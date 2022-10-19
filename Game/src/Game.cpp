#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	srand(time(nullptr));
	triangle = CreateTriangle();
	quad = CreateQuad();

	triangle->SetColorTint(1, 0, 0, 0.2f);
	triangle->SetPosition(0.7f, 0.7f, 0.0f);
	triangle->SetScale(0.3f, 0.3f, 0.0f);

	quad->SetColorTint(0, 1, 1, 0.1f);
	quad->SetPosition(-0.7f, 0.7f, 0.0f);
	quad->SetScale(0.3f, 0.3f, 0.0f);

	Texture* texture = new Texture("res/sprite1.png");
	sprite1 = CreateSprite(texture);
	Texture* texture2 = new Texture("res/sprite2.png");
	sprite2 = CreateSprite(texture2);
	Texture* texture3 = new Texture("res/sprite3.png");
	sprite3 = CreateSprite(texture3);

	sprite1->SetColorTint(1, 1, 1, 0.3f);
	sprite1->SetPosition(-0.7f, -0.7f, 0.0f);
	sprite1->SetScale(0.5f, 0.5f, 0.0f);

	sprite2->SetColorTint(1, 0, 0, 0.5f);
	sprite2->SetPosition(0.0f, 0.05f, 1.0f);
	sprite2->SetScale(0.5f, 0.5f, 0.0f);

	sprite3->SetColorTint(0, 0, 1, 0.5f);
	sprite3->SetPosition(0.0f, 0.05f, 0.0f);
	sprite3->SetScale(1.0f, 1.0f, 0.0f);
}

void Game::Inputs()
{
	glm::vec3 pos = sprite2->GetPosition();
	glm::vec3 rot = sprite2->GetRotation();
	glm::vec3 scale = sprite2->GetScale();

	if (IsKey(KeyState::KEY_HOLD, KeyCode::W))
		pos.y += 0.1f;
	if (IsKey(KeyState::KEY_HOLD, KeyCode::A))
		pos.x -= 0.1f;
	if (IsKey(KeyState::KEY_HOLD, KeyCode::S))
		pos.y -= 0.1f;
	if (IsKey(KeyState::KEY_HOLD, KeyCode::D))
		pos.x += 0.1f;

	if (IsKey(KeyState::KEY_PRESS, KeyCode::Q))
		rot.z += 0.1f;
	if (IsKey(KeyState::KEY_PRESS, KeyCode::E))
		rot.z -= 0.1f;

	if (IsKey(KeyState::KEY_RELEASE, KeyCode::Z))
	{
		scale.x += 0.25f;
		scale.y += 0.25f;
		scale.z += 0.25f;
	}
	if (IsKey(KeyState::KEY_RELEASE, KeyCode::X))
	{
		scale.x -= 0.25f;
		scale.y -= 0.25f;
		scale.z -= 0.25f;
	}
	sprite2->SetPosition(pos);
	sprite2->SetRotation(rot, false);
	sprite2->SetScale(scale);
}

void Game::Update()
{
	indexDraw++;
	
	//sprite3->SetColorTint(GetRandom(), GetRandom(), GetRandom(), 1);
	sprite1->SetRotation(0, 0, indexDraw / 90, true);
	sprite2->SetRotation(0, 0, -indexDraw / 90,true);
	triangle->SetRotation(0, 0, indexDraw / 90, true);
	quad->SetRotation(0, 0, -indexDraw / 90, true);
}

void Game::Draw()
{
	sprite3->Draw();
	sprite2->Draw();
	sprite1->Draw();
	quad->Draw();
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
	delete sprite1;
	delete sprite2;
	delete sprite3;
}