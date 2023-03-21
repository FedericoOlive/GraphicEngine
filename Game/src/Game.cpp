#include "Game.h"
#include <time.h>

void MouseMovement(double xPos, double yPos)
{
	std::cout << "Mouse Pos: {" << xPos << ", " << yPos << "}\n";
}

void MouseScrollMovement(double xOffset, double yOffset)
{
	std::cout << "Mouse Scroll: {" << xOffset << ", " << yOffset << "}\n";
}

void Game::Initialize()
{
	//floor = new GameObject("Floor");
	
	player = new GameObject("Player");
	//player->transform->SetParent(floor->transform);
	player->AddComponent(CreateQuad());
	player->transform->SetWorldPosition(glm::vec3(0, 0, 25));
	player->transform->SetScale(glm::vec3(100, 100, 100));

	camera = new GameObject("Camera");
	cam = new Camera(1280, 720);
	camera->AddComponent(cam);

	//cam->SetCameraPerspective(60, 0.1f, 1000.0f);
	target = player;

	Input::OnMouseMove.AddListener(MouseMovement);
	Input::OnMouseScrollMove.AddListener(MouseScrollMovement);
}

void Game::Inputs()
{
	Transform t = *target->transform;
	if (IsKeyDown(KeyCode::W)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0,  1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::A)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(-1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::S)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, -1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::D)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3( 1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Q)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, 0,  1 * multiply)); }
	if (IsKeyDown(KeyCode::E)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, 0, -1 * multiply)); }
	if (IsKeyDown(KeyCode::Z)) { multiply += 1; }
	if (IsKeyDown(KeyCode::X)) { multiply -= 1; }
	if (IsKeyDown(KeyCode::Num0)) { target = camera; }
	if (IsKeyDown(KeyCode::Num1)) { target = player; }
	if (IsKeyDown(KeyCode::Num2)) {}
	if (IsKeyDown(KeyCode::Num3)) {}
	if (IsKeyDown(KeyCode::Num4)) { target->transform->SetRotation(t.GetRotation() + glm::vec3(01 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Num5)) { target->transform->SetRotation(t.GetRotation() + glm::vec3(-1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Num6)) { target->transform->SetRotation(t.GetRotation() + glm::vec3(0, 01 * multiply, 0)); }
	if (IsKeyDown(KeyCode::Num7)) { target->transform->SetRotation(t.GetRotation() + glm::vec3(0, -1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::Num8)) { target->transform->SetRotation(t.GetRotation() + glm::vec3(0, 0, 01 * multiply)); }
	if (IsKeyDown(KeyCode::Num9)) { target->transform->SetRotation(t.GetRotation() + glm::vec3(0, 0, -1 * multiply)); }

	//cout << "----------------------------- " << target->name << " -----------------------------\n";
	//cout << "Position: {" << t.GetWorldPosition().x << ", " << t.GetWorldPosition().y << ", " << t.GetWorldPosition().z << "}\n";
	//cout << "Rotation: {" << t.GetRotation().x << ", " << t.GetRotation().y << ", " << t.GetRotation().z << "}\n";
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