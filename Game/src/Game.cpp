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
	Sprite* sprite = CreateSprite(miniGokuTexture);
	
	player = new GameObject("Player");
	player->AddComponent(sprite);
	player->transform->SetWorldPosition(glm::vec3(0, 100, 0));
	player->transform->SetLocalScale(glm::vec3(1, 1, 1));

	cameraPivot = new GameObject("Camera Pivot");
	cameraPivot->transform->SetParent(player);
	
	camera = new GameObject("Camera");
	camera->AddComponent(sprite);
	camera->transform->SetParent(cameraPivot);
	camera->transform->SetLocalPosition({ 0, 0, -100 });
	
	Camera* cam = new Camera(1280, 720);
	camera->AddComponent(cam);
	
	CharacterController* movementPlayer = new CharacterController();
	movementPlayer->RemoveRotation(false, true);
	CharacterController* movementCamPivot = new CharacterController();
	movementCamPivot->RemoveMovement();
	movementCamPivot->RemoveRotation(true, false);
	
	objectFoward = new GameObject("miniGoku3");
	objectFoward->AddComponent(CreateSprite(miniGokuTexture));
	objectFoward->transform->SetLocalScale({5, 5, 5});

	player->AddComponent(movementPlayer);
	cameraPivot->AddComponent(movementCamPivot);
	

	cube = new GameObject("The Cube");
	cube->AddComponent(CreateCube());
	cube->transform->SetWorldScale({ 10, 10, 10 });
	cube->transform->SetWorldRotation({ -90, 0, 0 });
	cube->transform->SetWorldPosition({ 0, 50, 0 });

	cube2 = new GameObject("The Cube");
	cube2->AddComponent(CreateCube());
	cube2->transform->SetParent(cube);
	cube2->transform->SetLocalScale({ 1, 1, 1 });
	cube2->transform->SetLocalPosition({ 0, 0, 20 });

	cube3 = new GameObject("The Cube");
	cube3->AddComponent(CreateCube());
	cube3->transform->SetParent(cube2);
	cube3->transform->SetLocalScale({ 1, 1, 1 });
	cube3->transform->SetLocalPosition({ 0, 0, -10 });

	
	target = cube->transform;
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
	ShowChildrens(player->transform, "");
	//cout << "----------------------------- " << target->gameObject->name << " -----------------------------\n";
	//cout << "Position: {" << target->GetLocalPosition().x << ", " << target->GetLocalPosition().y << ", " << target->GetLocalPosition().z << "}\n";
	//cout << "Rotation: {" << target->GetLocalRotation().x << ", " << target->GetLocalRotation().y << ", " << target->GetLocalRotation().z << "}\n";
}

void Game::Update()
{

	objectFoward->transform->SetWorldPosition(cube->transform->GetWorldPosition() + cube->transform->forward * 10.0f);
	return;
	glm::vec3 pos = player->transform->GetWorldPosition();
	glm::vec3 forward = player->transform->forward;

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

	worldContent = new GameObject("World Content");
	worldContent->transform->SetLocalPosition({ 0, 0, 0 });
	worldContent->transform->SetLocalScale({ 1, 1, 1 });
	worldContent->transform->SetLocalRotation({ 0, 0, 0 });

	floor = new GameObject("Floor");
	floor->AddComponent(CreateSprite(new Texture("res/Layer2.png")));
	floor->transform->SetLocalPosition({ 0, 0, 0 });
	floor->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	floor->transform->SetLocalRotation({ 90, 0, 0 });

	wallRight = new GameObject("Wall Right");
	wallRight->transform->SetParent(worldContent);
	wallRight->AddComponent(CreateSprite(new Texture("res/Layer3.png")));
	wallRight->transform->SetLocalPosition({ cubeDimensions, cubeDimensions / 2, 0 });
	wallRight->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallRight->transform->SetLocalRotation({ 0, -90, 0 });

	wallLeft = new GameObject("Wall Left");
	wallLeft->transform->SetParent(worldContent);
	wallLeft->AddComponent(CreateSprite(new Texture("res/Layer4.png")));
	wallLeft->transform->SetLocalPosition({ -cubeDimensions, cubeDimensions / 2, 0 });
	wallLeft->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallLeft->transform->SetLocalRotation({ 0, 90, 0 });

	wallBack = new GameObject("Wall Back");
	wallBack->transform->SetParent(worldContent);
	wallBack->AddComponent(CreateSprite(new Texture("res/Layer5.png")));
	wallBack->transform->SetLocalPosition({ 0, cubeDimensions / 2, -cubeDimensions });
	wallBack->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallBack->transform->SetLocalRotation({ 0, 180, 0 });

	wallFront = new GameObject("Wall Front");
	wallFront->transform->SetParent(worldContent);
	wallFront->AddComponent(CreateSprite(new Texture("res/Layer6.png")));
	wallFront->transform->SetLocalPosition({ 0, cubeDimensions / 2, cubeDimensions });
	wallFront->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0 });
	wallFront->transform->SetLocalRotation({ 0, 0, 0 });
}

void Game::ShowChildrens(Transform* transf, string preText)
{
	std::cout << preText << "* " << transf->gameObject->name << " Pos: " << AsString(transf->GetWorldPosition()) << " Rot: " << AsString(transf->GetWorldRotation()) << " foward: " << AsString(transf->forward) << "\n";
	preText += "\t";
	for (auto iter = transf->childrens.begin(); iter != transf->childrens.end(); ++iter)
	{
		ShowChildrens((*iter), preText);
	}
}

std::string Game::AsString(glm::vec3 pos)
{
	std::string text = "{ " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z) + " }";
	return text;
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