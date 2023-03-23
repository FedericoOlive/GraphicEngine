#include "Game.h"
#include <time.h>

void OnMouseMove(double xPos, double yPos)
{
	//std::cout << "Mouse Pos: {" << xPos << ", " << yPos << "}\n";
}

void MouseScrollMovement(double xOffset, double yOffset)
{
	//std::cout << "Mouse Scroll: {" << xOffset << ", " << yOffset << "}\n";
}

void Game::Initialize()
{
	float cubeDimensions = 250.0f;

	worldContent = new GameObject("World Content");

	floor = new GameObject("Floor");
	floor->AddComponent(CreateSprite(new Texture("res/Layer2.png")));
	floor->transform->SetWorldPosition(glm::vec3(0, -cubeDimensions, 0));
	floor->transform->SetScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	floor->transform->SetRotation(glm::vec3(90, 0, 0));

	wallRight = new GameObject("Wall Right");
	wallRight->AddComponent(CreateSprite(new Texture("res/Layer3.png")));
	wallRight->transform->SetWorldPosition(glm::vec3(cubeDimensions, 0, 0));
	wallRight->transform->SetScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallRight->transform->SetRotation(glm::vec3(0, -90, 0));

	wallLeft = new GameObject("Wall Left");
	wallLeft->AddComponent(CreateSprite(new Texture("res/Layer4.png")));
	wallLeft->transform->SetWorldPosition(glm::vec3(-cubeDimensions, 0, 0));
	wallLeft->transform->SetScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallLeft->transform->SetRotation(glm::vec3(0, 90, 0));

	wallBack = new GameObject("Wall Back");
	wallBack->AddComponent(CreateSprite(new Texture("res/Layer5.png")));
	wallBack->transform->SetWorldPosition(glm::vec3(0, 0, -cubeDimensions));
	wallBack->transform->SetScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallBack->transform->SetRotation(glm::vec3(0, 180, 0));

	wallFront = new GameObject("Wall Front");
	wallFront->AddComponent(CreateSprite(new Texture("res/Layer6.png")));
	wallFront->transform->SetWorldPosition(glm::vec3(0, 0, cubeDimensions));
	wallFront->transform->SetScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallFront->transform->SetRotation(glm::vec3(0, 0, 0));

	wallRight->transform->SetParent(worldContent);
	wallLeft->transform->SetParent(worldContent);
	wallBack->transform->SetParent(worldContent);
	wallFront->transform->SetParent(worldContent);

	Input::OnMouseMove.AddListener(OnMouseMove);
	Input::OnMouseScrollMove.AddListener(MouseScrollMovement);


	player = new GameObject("Player");
	player->AddComponent(CreateSprite(new Texture("res/Goku.png")));
	player->transform->SetWorldPosition(glm::vec3(0, 0, 0));
	player->transform->SetScale(glm::vec3(100, 100, 100));
	cam = new Camera(1280, 720);
	player->AddComponent(cam);
	CameraController* camController = new CameraController(cam);
	player->AddComponent(camController);
	camController->SetThirdPersonDefault();
	target = player;
}

void Game::Inputs()
{
	Transform t = *target->transform;
	if (IsKeyDown(KeyCode::Q)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, 0,  1 * multiply)); }
	if (IsKeyDown(KeyCode::E)) { target->transform->SetWorldPosition(t.GetWorldPosition() + glm::vec3(0, 0, -1 * multiply)); }
	if (IsKeyDown(KeyCode::Z)) { multiply += 1; }
	if (IsKeyDown(KeyCode::X)) { multiply -= 1; }
	if (IsKeyDown(KeyCode::Num0)) { }
	if (IsKeyDown(KeyCode::Num1)) { LockCursor(true);  }
	if (IsKeyDown(KeyCode::Num2)) { LockCursor(false); }
	if (IsKeyDown(KeyCode::Num3)) { }
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