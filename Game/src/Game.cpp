#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	camera = CreateCamera({ 0,0 }, { 1280, 720 }, Camera::Perspective, true);
	
	targetFloatModify = &multiply;
	SetLights();
	AddListeners();
	AddPlayer();
	AddMinimap();
	SetEnviroment();
	AddBSP();
	
	target = cubeContent->transform;
}

void Game::Inputs()
{
	if (Input::IsKeyDown(KeyCode::Kp9)) { ChangeColorSpotLight(); }
	
	if (Input::IsKeyHolding(KeyCode::Q)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3( 1 * multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::E)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3(-1 * multiply, 0, 0)); }

	if (Input::IsKeyHolding(KeyCode::Z)) { *targetFloatModify -= 1.01f; cout << targetString << (*targetFloatModify) << "\n"; }
	if (Input::IsKeyHolding(KeyCode::X)) { *targetFloatModify += 1.01f; cout << targetString << (*targetFloatModify) << "\n"; }

	if (Input::IsKeyHolding(KeyCode::Kp2)) { cubeControll->transform->SetLocalPosition(cubeControll->transform->GetLocalPosition() + glm::vec3(0, 0, 1 * multiply)); }
	if (Input::IsKeyHolding(KeyCode::Kp4)) { cubeControll->transform->SetLocalPosition(cubeControll->transform->GetLocalPosition() + glm::vec3(1 * -multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::Kp6)) { cubeControll->transform->SetLocalPosition(cubeControll->transform->GetLocalPosition() + glm::vec3(1 * multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::Kp8)) { cubeControll->transform->SetLocalPosition(cubeControll->transform->GetLocalPosition() + glm::vec3(0, 0, 1 * -multiply)); }
	if (Input::IsKeyHolding(KeyCode::Kp7)) { cubeControll->transform->SetLocalPosition(cubeControll->transform->GetLocalPosition() + glm::vec3(0, 1 * -multiply, 0)); }
	if (Input::IsKeyHolding(KeyCode::Kp9)) { cubeControll->transform->SetLocalPosition(cubeControll->transform->GetLocalPosition() + glm::vec3(0, 1 * multiply, 0)); }
	if (Input::IsKeyHolding(KeyCode::Num0)) {  }
	if (Input::IsKeyHolding(KeyCode::Num1)) { LockCursor(true);  }
	if (Input::IsKeyHolding(KeyCode::Num2)) { LockCursor(false); }
	if (Input::IsKeyHolding(KeyCode::Num3)) { player->transform->SetLocalPosition(player->transform->GetLocalPosition() + glm::vec3(0 , -1 * multiply, 0)); }
	if (Input::IsKeyHolding(KeyCode::Num4)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(01 * multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::Num5)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(-1 * multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::Num6)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, 01 * multiply, 0)); }
	if (Input::IsKeyHolding(KeyCode::Num7)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, -1 * multiply, 0)); }
	if (Input::IsKeyHolding(KeyCode::Num8)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, 0, 01 * multiply)); }
	if (Input::IsKeyHolding(KeyCode::Num9)) { target->SetLocalRotation(target->GetLocalRotation() + glm::vec3(0, 0, -1 * multiply)); }

	if (Input::IsKeyDown(KeyCode::H)) { ShowHierarchyInConsole(); }

	if (Input::IsKeyHolding(KeyCode::Space)) { player->transform->SetLocalPosition(player->transform->GetLocalPosition() + glm::vec3(0, 1 * multiply, 0)); }
	if (Input::IsKeyHolding(KeyCode::LeftControl)) { player->transform->SetLocalPosition(player->transform->GetLocalPosition() + glm::vec3(0, -1 * multiply, 0)); }
	if (Input::IsKeyHolding(KeyCode::BackSpace)) { player->transform->SetLocalPosition(player->transform->GetLocalPosition() + glm::vec3(0, -1 * multiply, 0)); }
}

void Game::Update()
{
	float time = Timer::ElapsedTime();
}

void Game::Draw()
{
	//DrawCubeLines(cubeContent->transform->aabbGlobal, 2, Color::Blue, camera);
	//DrawCubeLines(cubeContent->transform->aabbGlobal, 2, Color::Blue, cameraMinimap);
}

void Game::SetLights()
{
	GameObject* goLightDir01 = CreateGameObject("Dir Light 1");
	goLightDir01->transform->SetWorldRotation({ -45, 0, 0 });
	goLightDir01->transform->SetWorldPosition({ 0, 100, 0 });

	DirectionalLight* lightDir1 = CreateDirectionalLight();
	lightDir1->powerDiffuse = 2;
	goLightDir01->AddComponent(lightDir1);
}

void Game::SetEnviroment()
{
	CreateSkybox("res/Skybox/Skybox_Right.jpg", "res/Skybox/Skybox_Left.jpg", "res/Skybox/Skybox_Top.jpg", "res/Skybox/Skybox_Bottom.jpg", "res/Skybox/Skybox_Front.jpg", "res/Skybox/Skybox_Back.jpg");

	cubeControll = CreateGameObject("Cube 1");
	cubeControll->transform->SetWorldPosition({ 0, 2, 0 });
	Cube* cubeControllCubeComponent = CreateCube();
	cubeControllCubeComponent->SetTexture(CreateTexture("res/Layer9.png"));
	cubeControll->AddComponent(cubeControllCubeComponent);
	Collider* colControll = CreateCollider();
	cubeControll->AddComponent(colControll);

	floorTexture = CreateTexture("res/Layer2.png");
	wallRightTexture = CreateTexture("res/World/Right.png");
	wallLeftTexture = CreateTexture("res/World/Left.png");
	wallBackTexture = CreateTexture("res/World/Back.png");
	wallFrontTexture = CreateTexture("res/World/Front.png");

	GameObject* WorldContent = CreateGameObject("World Content");
	float dimension = 20;

	for (float i = -1; i <= 1; i += 1)
	{
		for (float j = -1; j <= 0; j += 1)
		{
			if(i==-1&&j==-1)
				continue;
			if(i==1&&j==-1)
				continue;

			CreateRoom(WorldContent, { i * dimension + i, 0, j * dimension + j }, dimension * 0.5f);
		}
	}


	// 4 Cubes
	cubeContent = CreateGameObject("Cube Content");

	float distance = 10;

	cube1 = CreateGameObject("Cube 1");
	cube1->transform->SetParent(cubeContent);
	cube1->transform->SetWorldPosition({ 0, 0, 0 });
	Cube* cube1CubeComponent = CreateCube();
	//cube1CubeComponent->SetTexture(CreateTexture("res/Layer9.png"));
	cube1->AddComponent(cube1CubeComponent);
	Collider* col1 = CreateCollider();
	cube1->AddComponent(col1);

	cube2 = CreateGameObject("Cube 2");
	cube2->transform->SetParent(cubeContent);
	cube2->transform->SetWorldPosition({ distance, 0, 0 });
	Cube* cube2CubeComponent = CreateCube();
	cube2->AddComponent(cube2CubeComponent);
	Collider* col2 = CreateCollider();
	cube2->AddComponent(col2);

	cube3 = CreateGameObject("Cube 3");
	cube3->transform->SetParent(cubeContent);
	cube3->transform->SetWorldPosition({ -distance, 0, 0 });
	Cube* cube3CubeComponent = CreateCube();
	cube3->AddComponent(cube3CubeComponent);
	Collider* col3 = CreateCollider();
	cube3->AddComponent(col3);

	cube4 = CreateGameObject("Cube 4");
	cube4->transform->SetParent(cubeContent);
	cube4->transform->SetWorldPosition({ 0, 0, -distance });
	Cube* cube4CubeComponent = CreateCube();
	cube4->AddComponent(cube4CubeComponent);
	Collider* col4 = CreateCollider();
	cube4->AddComponent(col4);

	cube4CubeComponent->SetColorTint(81 / 255.0f, 209 / 255.0f, 246 / 255.0f, 0.5f);

	cubeContent->transform->SetWorldScale({ 2, 2, 2 });
	cubeContent->transform->SetWorldPosition({ 0, 1, 0 });
}

void Game::CreateRoom(GameObject* WorldContent, glm::vec3 position, float dimension)
{
	float cubeDimensions = 1.0f;
	GameObject* roomContent = CreateGameObject("Room Content");
	roomContent->transform->SetLocalPosition(position);
	roomContent->transform->SetParent(WorldContent);

	GameObject* floor = CreateGameObject("Floor");
	Sprite* floorSprite = CreateSprite(floorTexture);
	floor->transform->SetParent(roomContent);
	floor->AddComponent(floorSprite);
	floor->transform->SetLocalPosition({ 0, 0, 0 });
	floor->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	floor->transform->SetLocalRotation({ 90, 180, 0 });
	floorSprite->material->shininess = 10000;
	floorSprite->material->specular = { 0, 0, 0 };
	floorSprite->material->diffuse = { 0.5f, 0.5f, 0.5f };

	GameObject* wallRight = CreateGameObject("Wall Right");
	wallRight->transform->SetParent(roomContent);
	wallRight->AddComponent(CreateSprite(wallRightTexture));
	wallRight->transform->SetLocalPosition({ cubeDimensions, cubeDimensions, 0 });
	wallRight->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0.01f });
	wallRight->transform->SetLocalRotation({ 0, -90, 0 });
	wallRight->AddComponent(CreateCollider());

	GameObject* wallLeft = CreateGameObject("Wall Left");
	wallLeft->transform->SetParent(roomContent);
	wallLeft->AddComponent(CreateSprite(wallLeftTexture));
	wallLeft->transform->SetLocalPosition({ -cubeDimensions, cubeDimensions, 0 });
	wallLeft->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallLeft->transform->SetLocalRotation({ 0, 90, 0 });
	wallLeft->AddComponent(CreateCollider());

	GameObject* wallBack = CreateGameObject("Wall Back");
	wallBack->transform->SetParent(roomContent);
	wallBack->AddComponent(CreateSprite(wallBackTexture));
	wallBack->transform->SetLocalPosition({ 0, cubeDimensions, cubeDimensions });
	wallBack->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallBack->transform->SetLocalRotation({ 0, 180, 0 });
	wallBack->AddComponent(CreateCollider());

	GameObject* wallFront = CreateGameObject("Wall Front");
	wallFront->transform->SetParent(roomContent);
	wallFront->AddComponent(CreateSprite(wallFrontTexture));
	wallFront->transform->SetLocalPosition({ 0, cubeDimensions, -cubeDimensions });
	wallFront->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallFront->transform->SetLocalRotation({ 0, 0, 0 });
	wallFront->AddComponent(CreateCollider());

	roomContent->transform->SetLocalScale({ dimension, dimension / 10.0f, dimension });
}

void Game::AddListeners()
{
	std::function<void(double, double)> onMouseMove = [this](double x, double y) { OnMouseMove(x, y); };
	Input::OnMouseMove.AddListener(onMouseMove);
	
	std::function<void(double, double)> onMouseScrollMovement = [this](double x, double y) { OnMouseScrollMovement(x, y); };
	Input::OnMouseScrollMove.AddListener(onMouseScrollMovement);
}

void Game::AddPlayer()
{
	player = CreateCharacterController(camera);
	//player->movement->RemoveMovement();
	player->SetThirdPerson();
	player->transform->SetWorldPosition(glm::vec3(0, 18, 42));
	
	player->visualPlayer->AddComponent(CreateCube());
	
	GameObject* spotGo = CreateGameObject("SpotLight Player");
	spotlightPlayer = CreateSpotLight();
	spotGo->AddComponent(spotlightPlayer);
	spotGo->transform->SetParent(player->pivot);

	Collider* col = CreateCollider(false);
	player->visualPlayer->transform->gameObject->AddComponent(col);
}

void Game::AddMinimap()
{
	GameObject* cameraMinimapGo = CreateGameObject("Camera MiniMap");
	cameraMinimapGo->transform->SetWorldPosition({ -50, 100, 50 });
	cameraMinimapGo->transform->SetWorldRotation({ -90, 0, 0 });
	cameraMinimap = CreateCamera({ 0, 720 - 200 }, { 200, 200 }, Camera::Orthogonal, true);
	cameraMinimap->SetZoom(2.0f);
	cameraMinimapGo->AddComponent(cameraMinimap);
}

void Game::ChangeColorSpotLight()
{
	currentColor++;
	if (currentColor > 3) 
		currentColor = 0;
	
	switch (currentColor)
	{
	case 0:
		spotlightPlayer->diffuse = { 1, 1, 1 };
		break;
	case 1:
		spotlightPlayer->diffuse = { 1, 0, 0 };
		break;
	case 2:
		spotlightPlayer->diffuse = { 0, 1, 0 };
		break;
	case 3:
		spotlightPlayer->diffuse = { 0, 0, 1 };
		break;
	default:
		break;
	}
}

void Game::OnMouseMove(double xPos, double yPos)
{
	//std::cout << "Mouse Pos: {" << xPos << ", " << yPos << "}\n";
}

void Game::OnMouseScrollMovement(double xOffset, double yOffset)
{
	glm::vec3 minPlayerZoom = { 0, -5, -15 };
	glm::vec3 maxPlayerZoom = { 0, 5, 15 };

	playerZoom.y += 1.0f * multiply * static_cast<float>(-yOffset);
	playerZoom.z += 3.0f * multiply * static_cast<float>(-yOffset);

	if (playerZoom.y > maxPlayerZoom.y) playerZoom = maxPlayerZoom;
	if (playerZoom.y < minPlayerZoom.y) playerZoom = minPlayerZoom;

	if (playerZoom.y > 0)
	{
		player->SetThirdPerson(playerZoom);
		camera->SetZoom(1);
	}
	else
	{
		player->SetFirstPerson();
		camera->SetZoom(1 - (-playerZoom.y / 10.0f));
	}
}

void Game::AddBSP()
{
	CreateBinarySpacePartitioning(cubeControll->transform);

	Transform* bsp1 = CreateGameObject("BSP 1")->transform;
	bsp1->SetWorldPosition({ 0, 0, -10.5f });
	bsp1->SetWorldRotation({ 0, 0, 0 });
	AddPlaneBSP(bsp1);

	Transform* bsp2 = CreateGameObject("BSP 2")->transform;
	bsp2->SetWorldPosition({ -10.5f, 0, 0 });
	bsp2->SetWorldRotation({ 0, -90, 0 });
	AddPlaneBSP(bsp2);

	Transform* bsp3 = CreateGameObject("BSP 3")->transform;
	bsp3->SetWorldPosition({ 10.5f, 0, 0 });
	bsp3->SetWorldRotation({ 0, 90, 0 });
	AddPlaneBSP(bsp3);
}

void Game::DeInitialize()
{

}