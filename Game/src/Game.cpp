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
	SetEnviroment();
	AddListeners();

	Texture* miniGokuTexture = new Texture("res/Goku.png");
	Texture* playerCubeTexture = new Texture("res/Layer9.png");
	Sprite* sprite = CreateSprite(miniGokuTexture);
	
	player = CreateGameObject("Player");
	Cube* playerCube = CreateCube();
	playerCube->SetTexture(playerCubeTexture);
	player->AddComponent(CreateCube());
	player->transform->SetWorldPosition(glm::vec3(0, 10, 0));
	player->transform->SetLocalScale(glm::vec3(1, 1, 1));

	cameraPivot = CreateGameObject("Camera Pivot");
	cameraPivot->transform->SetLocalPosition({ 0, 1, 0 });
	cameraPivot->transform->SetParent(player);
	
	camera = CreateGameObject("Camera");
	camera->transform->SetParent(cameraPivot);
	camera->transform->SetLocalPosition({ 0, 0, 5 });
	
	Camera* cam = new Camera(1280, 720);
	camera->AddComponent(cam);
	
	CharacterController* movementPlayer = new CharacterController();
	movementPlayer->RemoveRotation(false, true);
	CharacterController* movementCamPivot = new CharacterController();
	movementCamPivot->RemoveMovement();
	movementCamPivot->RemoveRotation(true, false);
	
	objectFoward = CreateGameObject("miniGoku3");
	objectFoward->AddComponent(CreateSprite(miniGokuTexture));
	objectFoward->transform->SetLocalScale({5, 5, 5});

	player->AddComponent(movementPlayer);
	cameraPivot->AddComponent(movementCamPivot);
	

	cubeContent = CreateGameObject("Cube Content");
	cubeContent->transform->SetWorldScale({ 10, 10, 10 });
	cubeContent->transform->SetWorldPosition({ 0, 5, 0 });
	float distance = 2;
	cube1 = CreateGameObject("Cube 1");
	cube1->transform->SetParent(cubeContent);
	cube1->AddComponent(playerCube);
	cube1->transform->SetLocalPosition({ distance, 0, distance });

	cube2 = CreateGameObject("Cube 2");
	cube2->transform->SetParent(cubeContent);
	cube2->AddComponent(CreateCube());
	cube2->transform->SetLocalPosition({ distance, 0, -distance });

	cube3 = CreateGameObject("Cube 3");
	cube3->transform->SetParent(cubeContent);
	cube3->AddComponent(CreateCube());
	cube3->transform->SetLocalPosition({ -distance, 0, distance });

	cube4 = CreateGameObject("Cube 4");
	cube4->transform->SetParent(cubeContent);
	cube4->AddComponent(CreateCube());
	cube4->transform->SetLocalPosition({ -distance, 0, -distance });
		
	target = cubeContent->transform;
}

void Game::Inputs()
{
	if (IsKeyDown(KeyCode::Q)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3(1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::E)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3(-1 * multiply,0, 0)); }
	if (IsKeyDown(KeyCode::Z)) { multiply += 1; }
	if (IsKeyDown(KeyCode::X)) { multiply -= 1; }
	if (IsKeyDown(KeyCode::Num0)) { target == camera->transform ? target = player->transform : target = camera->transform; }
	if (IsKeyDown(KeyCode::Num1)) { LockCursor(true);  }
	if (IsKeyDown(KeyCode::Num2)) { LockCursor(false); }
	if (IsKeyDown(KeyCode::Num3)) {  }
	if (IsKeyDown(KeyCode::Num4)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(01 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Num5)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(-1 * multiply, 0, 0)); }
	if (IsKeyDown(KeyCode::Num6)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, 01 * multiply, 0)); }
	if (IsKeyDown(KeyCode::Num7)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, -1 * multiply, 0)); }
	if (IsKeyDown(KeyCode::Num8)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, 0, 01 * multiply)); }
	if (IsKeyDown(KeyCode::Num9))
	{
		target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, 0, -1 * multiply));
	}
	if (IsKeyPressed(KeyCode::P)) { ShowHierarchyInConsole(); }

	
	//cout << "----------------------------- " << target->gameObject->name << " -----------------------------\n";
	//cout << "Position: {" << target->GetLocalPosition().x << ", " << target->GetLocalPosition().y << ", " << target->GetLocalPosition().z << "}\n";
	//cout << "Rotation: {" << target->GetLocalRotation().x << ", " << target->GetLocalRotation().y << ", " << target->GetLocalRotation().z << "}\n";
}

void Game::Update()
{
	objectFoward->transform->SetWorldPosition(cubeContent->transform->GetWorldPosition() + cubeContent->transform->forward() * 10.0f);
	return;
	glm::vec3 pos = player->transform->GetWorldPosition();
	glm::vec3 forward = player->transform->forward();

	Transform t = *player->transform;
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

void Game::SetEnviroment()
{
	float cubeDimensions = 250.0f;

	worldContent = CreateGameObject("World Content");
	worldContent->transform->SetLocalPosition({ 0, 0, 0 });
	worldContent->transform->SetLocalScale({ 1, 1, 1 });
	worldContent->transform->SetLocalRotation({ 0, 0, 0 });

	floor = CreateGameObject("Floor");
	floor->AddComponent(CreateSprite(new Texture("res/Layer2.png")));
	floor->transform->SetLocalPosition({ 0, 0, 0 });
	floor->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	floor->transform->SetLocalRotation({ 90, 0, 0 });

	wallRight = CreateGameObject("Wall Right");
	wallRight->transform->SetParent(worldContent);
	wallRight->AddComponent(CreateSprite(new Texture("res/Layer3.png")));
	wallRight->transform->SetLocalPosition({ cubeDimensions, cubeDimensions / 2, 0 });
	wallRight->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallRight->transform->SetLocalRotation({ 0, -90, 0 });

	wallLeft = CreateGameObject("Wall Left");
	wallLeft->transform->SetParent(worldContent);
	wallLeft->AddComponent(CreateSprite(new Texture("res/Layer4.png")));
	wallLeft->transform->SetLocalPosition({ -cubeDimensions, cubeDimensions / 2, 0 });
	wallLeft->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallLeft->transform->SetLocalRotation({ 0, 90, 0 });

	wallBack = CreateGameObject("Wall Back");
	wallBack->transform->SetParent(worldContent);
	wallBack->AddComponent(CreateSprite(new Texture("res/Layer5.png")));
	wallBack->transform->SetLocalPosition({ 0, cubeDimensions / 2, -cubeDimensions });
	wallBack->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallBack->transform->SetLocalRotation({ 0, 180, 0 });

	wallFront = CreateGameObject("Wall Front");
	wallFront->transform->SetParent(worldContent);
	wallFront->AddComponent(CreateSprite(new Texture("res/Layer6.png")));
	wallFront->transform->SetLocalPosition({ 0, cubeDimensions / 2, cubeDimensions });
	wallFront->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallFront->transform->SetLocalRotation({ 0, 0, 0 });
}

void Game::AddListeners()
{
	Input::OnMouseMove.AddListener(OnMouseMove);
	Input::OnMouseScrollMove.AddListener(MouseScrollMovement);
}

void Game::DeInitialize()
{
	delete player;
	delete worldContent;
	delete floor;
	delete wallRight;
	delete wallLeft;
	delete wallBack;
	delete wallFront;
}