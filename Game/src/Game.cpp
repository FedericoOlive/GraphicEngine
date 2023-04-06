#include "Game.h"
#include <time.h>

Camera* camT;
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
	float cubeDimensions = 25.0f;

	worldContent = new GameObject("World Content");

	floor = new GameObject("Floor");
	floor->AddComponent(CreateSprite(new Texture("res/Layer2.png")));
	floor->transform->SetWorldPosition(glm::vec3(0, -cubeDimensions, 0));
	floor->transform->SetLocalScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	floor->transform->SetWorldRotation(glm::vec3(90, 0, 0));

	wallRight = new GameObject("Wall Right");
	wallRight->AddComponent(CreateSprite(new Texture("res/Layer3.png")));
	wallRight->transform->SetWorldPosition(glm::vec3(cubeDimensions, 0, 0));
	wallRight->transform->SetLocalScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallRight->transform->SetWorldRotation(glm::vec3(0, -90, 0));

	wallLeft = new GameObject("Wall Left");
	wallLeft->AddComponent(CreateSprite(new Texture("res/Layer4.png")));
	wallLeft->transform->SetWorldPosition(glm::vec3(-cubeDimensions, 0, 0));
	wallLeft->transform->SetLocalScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallLeft->transform->SetWorldRotation(glm::vec3(0, 90, 0));

	wallBack = new GameObject("Wall Back");
	wallBack->AddComponent(CreateSprite(new Texture("res/Layer5.png")));
	wallBack->transform->SetWorldPosition(glm::vec3(0, 0, -cubeDimensions));
	wallBack->transform->SetLocalScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallBack->transform->SetWorldRotation(glm::vec3(0, 180, 0));

	wallFront = new GameObject("Wall Front");
	wallFront->AddComponent(CreateSprite(new Texture("res/Layer6.png")));
	wallFront->transform->SetWorldPosition(glm::vec3(0, 0, cubeDimensions));
	wallFront->transform->SetLocalScale(glm::vec3(cubeDimensions * 2, cubeDimensions * 2, 0));
	wallFront->transform->SetWorldRotation(glm::vec3(0, 0, 0));

	wallRight->transform->SetParent(worldContent);
	wallLeft->transform->SetParent(worldContent);
	wallBack->transform->SetParent(worldContent);
	wallFront->transform->SetParent(worldContent);

	Input::OnMouseMove.AddListener(OnMouseMove);
	Input::OnMouseScrollMove.AddListener(MouseScrollMovement);

	player = new GameObject("Player");
	player->AddComponent(CreateSprite(new Texture("res/Goku.png")));
	player->transform->SetWorldPosition(glm::vec3(0, 0, 0));
	player->transform->SetLocalScale(glm::vec3(1, 1, 1));

	cam = new Camera(1280, 720);
	CameraController* camController = new CameraController(cam);
	player->AddComponent(cam);
	player->AddComponent(camController);
	//camController->SetThirdPersonDefault();
	camController->SetFirstPersonDefault();
	
	//miniGoku = new GameObject("miniGoku");
	//miniGoku->AddComponent(CreateSprite(new Texture("res/Goku.png")));
	//miniGoku->transform->SetLocalScale(glm::vec3(10, 10, 10));
	//
	//miniGoku2 = new GameObject("miniGoku");
	//miniGoku2->AddComponent(CreateSprite(new Texture("res/Goku.png")));
	//miniGoku2->transform->SetParent(miniGoku);
	//miniGoku2->transform->SetLocalScale(glm::vec3(10, 10, 10));
	//miniGoku2->transform->SetLocalPosition({ 10, 0, 0 });
}

void Game::Inputs()
{
	//target = miniGoku->transform;
	
	if (IsKeyDown(KeyCode::Q)) { target->SetWorldPosition(target->GetWorldPosition() + glm::vec3(0,  1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::E)) { target->SetWorldPosition(target->GetWorldPosition() + glm::vec3(0, -1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::Z)) { multiply += 1; }
	if (IsKeyDown(KeyCode::X)) { multiply -= 1; }
	if (IsKeyDown(KeyCode::Num0)) {  }
	if (IsKeyDown(KeyCode::Num1)) { LockCursor(true);  }
	if (IsKeyDown(KeyCode::Num2)) { LockCursor(false); }
	if (IsKeyDown(KeyCode::Num3)) { }
	if (IsKeyDown(KeyCode::Num4)) { target->SetWorldRotation(target->GetWorldRotation() + glm::vec3(01 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Num5)) { target->SetWorldRotation(target->GetWorldRotation() + glm::vec3(-1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Num6)) { target->SetWorldRotation(target->GetWorldRotation() + glm::vec3(0, 01 * multiply, 0)); }
	if (IsKeyDown(KeyCode::Num7)) { target->SetWorldRotation(target->GetWorldRotation() + glm::vec3(0, -1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::Num8)) { target->SetWorldRotation(target->GetWorldRotation() + glm::vec3(0, 0, 01 * multiply)); }
	if (IsKeyDown(KeyCode::Num9))
	{
		target->SetWorldRotation(target->GetWorldRotation() + glm::vec3(0, 0, -1 * multiply));
	}

	//cout << "----------------------------- " << target->name << " -----------------------------\n";
	//cout << "Position: {" << t.GetWorldPosition().x << ", " << t.GetWorldPosition().y << ", " << t.GetWorldPosition().z << "}\n";
	//cout << "Rotation: {" << target->GetWorldRotation().x << ", " << target->GetWorldRotation().y << ", " << target->GetWorldRotation().z << "}\n";
}

void Game::Update()
{
	return;
	glm::vec3 pos = player->transform->GetWorldPosition();
	glm::vec3 forward = player->transform->forward;

	Transform t = *miniGoku2->transform;
	cout << "----------------------------------------------------------\n";
	//cout << "MiniGoku Rotation: {" << t.GetWorldRotation().x << ", " << t.GetWorldRotation().y << ", " << t.GetWorldRotation().z << "}\n";
	//cout << "Player Position: {" << t.GetWorldPosition().x << ", " << t.GetWorldPosition().y << ", " << t.GetWorldPosition().z << "}\n";
	//t = *miniGoku2->transform;
	cout << "MiniGoku2 Position: {" << t.GetWorldPosition().x << ", " << t.GetWorldPosition().y << ", " << t.GetWorldPosition().z << "}\n";
	cout << "MiniGoku2 Rotation: {" << t.GetWorldRotation().x << ", " << t.GetWorldRotation().y << ", " << t.GetWorldRotation().z << "}\n";
}

void Game::Draw()
{

}

void Game::DeInitialize()
{
	delete target;
	delete player;
	delete worldContent;
	delete floor;
	delete wallRight;
	delete wallLeft;
	delete wallBack;
	delete wallFront;
}