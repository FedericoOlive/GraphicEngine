#include "Game.h"
#include <time.h>

void Game::Initialize()
{
	player = new GameObject();
	floor = new GameObject("Floor");
	player->transform->SetParent(floor->transform);
	player->AddComponent(CreateQuad());
	player->transform->SetWorldPosition(glm::vec3(1280/2, 720/2, 0));
	player->transform->SetScale(glm::vec3(100, 100, 100));
}

void Game::Inputs()
{
	Transform t = *player->transform;
	if (IsKeyDown(KeyCode::W)) { player->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, 1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::A)) { player->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(-1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::S)) { player->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, -1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::D)) { player->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Q)) { player->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, 0, 1 * multiply)); }
	if (IsKeyDown(KeyCode::E)) { player->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, 0, -1 * multiply)); }
	if (IsKeyDown(KeyCode::Z)) { multiply += 1; }
	if (IsKeyDown(KeyCode::X)) { multiply -= 1; }
	if (IsKeyDown(KeyCode::Num0)) {}
	if (IsKeyDown(KeyCode::Num1)) {}
	if (IsKeyDown(KeyCode::Num2)) {}
	if (IsKeyDown(KeyCode::Num3)) {}
	if (IsKeyDown(KeyCode::Num4)) {}
	if (IsKeyDown(KeyCode::Num5)) {}
	if (IsKeyDown(KeyCode::Num6)) {}
	if (IsKeyDown(KeyCode::Num7)) {}
	if (IsKeyDown(KeyCode::Num8)) {}
	if (IsKeyDown(KeyCode::Num9)) {}
}

void Game::Update()
{

}

void Game::Draw()
{

}

void Game::DeInitialize()
{
	delete player;
	delete floor;
}