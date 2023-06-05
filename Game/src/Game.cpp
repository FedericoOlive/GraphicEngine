#include "Game.h"
#include <time.h>

void Game::Initialize()
{
	camera = CreateCamera({ 0,0 }, { 1280, 720 }, Camera::Perspective, true);
	
	SetEnviroment();
	SetLights();
	AddListeners();
	AddPlayer();
	AddMinimap();	
	AddModels3D();
	
	target = cubeContent->transform;	
}

void Game::Inputs()
{
	if (Input::IsKeyDown(KeyCode::Kp0)) { cout << "KP0\n"; }
	if (Input::IsKeyDown(KeyCode::Kp1)) { cout << "KP1\n"; }
	if (Input::IsKeyDown(KeyCode::Kp2)) { cout << "KP2\n"; }
	if (Input::IsKeyDown(KeyCode::Kp3)) { cout << "KP3\n"; }
	if (Input::IsKeyDown(KeyCode::Kp4)) { cout << "KP4\n"; }
	if (Input::IsKeyDown(KeyCode::Kp5)) { cout << "KP5\n"; }
	if (Input::IsKeyDown(KeyCode::Kp6)) { cout << "KP6\n"; }
	if (Input::IsKeyDown(KeyCode::Kp7)) { cout << "KP7\n"; }
	if (Input::IsKeyDown(KeyCode::Kp8)) { cout << "KP8\n"; }
	if (Input::IsKeyDown(KeyCode::Kp9)) { cout << "KP9\n"; }	
	
	if (Input::IsKeyHolding(KeyCode::Q)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3(1 * multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::E)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3(-1 * multiply,0, 0)); }
	if (Input::IsKeyHolding(KeyCode::Z)) { multiply += 1; }
	if (Input::IsKeyHolding(KeyCode::X)) { multiply -= 1; if (multiply < 0)multiply = 0.01f; }
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
	objectFoward->transform->SetWorldPosition(cubeContent->transform->GetWorldPosition() + cubeContent->transform->forward() * 2.0f + glm::vec3{ 0, 5, 0 });
	float time = Timer::ElapsedTime();
	
	goLightPointArround01->transform->SetWorldPosition(glm::vec3{ glm::sin(time*0.2f) * 45, 10, glm::cos(time * 0.2f) * 45 });
	goLightPointArround02->transform->SetWorldPosition(glm::vec3{ glm::sin(time*0.4f) * 45, 15, glm::cos(time * 0.4f) * 45 });
	goLightPointArround03->transform->SetWorldPosition(glm::vec3{ glm::sin(time*0.8f) * 45, 20, glm::cos(time * 0.8f) * 45 });
	goLightPointArround04->transform->SetWorldPosition(glm::vec3{ glm::sin(time*1.6f) * 45, 25, glm::cos(time * 1.6f) * 45 });
}

void Game::Draw()
{

}

void Game::SetLights()
{
	GameObject* goLightDir01 = CreateGameObject("Dir Light 1");
	//GameObject* goLightDir02 = CreateGameObject("Dir Light 2");
	GameObject* goLightPoint01 = CreateGameObject("Point Light 1");
	GameObject* goLightPoint02 = CreateGameObject("Point Light 2");
	GameObject* goLightPoint03 = CreateGameObject("Point Light 3");
	GameObject* goLightPoint04 = CreateGameObject("Point Light 4");
	GameObject* goLightSpot01 = CreateGameObject("Spot Light 1");
	GameObject* goLightSpot02 = CreateGameObject("Spot Light 2");

	DirectionalLight* lightDir1 = CreateDirectionalLight();
	//DirectionalLight* lightDir2 = CreateDirectionalLight();
	PointLight* lightPoint1 = CreatePointLight();
	PointLight* lightPoint2 = CreatePointLight();
	PointLight* lightPoint3 = CreatePointLight();
	PointLight* lightPoint4 = CreatePointLight();
	SpotLight* lightSpot1 = CreateSpotLight();
	SpotLight* lightSpot2 = CreateSpotLight();

	goLightDir01->AddComponent(lightDir1);
	//goLightDir02->AddComponent(lightDir2);
	goLightPoint01->AddComponent(lightPoint1);
	goLightPoint02->AddComponent(lightPoint2);
	goLightPoint03->AddComponent(lightPoint3);
	goLightPoint04->AddComponent(lightPoint4);
	goLightSpot01->AddComponent(lightSpot1);
	goLightSpot02->AddComponent(lightSpot2);

	float distance = 40;	
	goLightDir01->transform->SetWorldPosition({ 0, 10, 0 });
	//goLightDir02->transform->SetWorldPosition({ 0, 10, 0 });
	//goLightDir02->transform->SetWorldRotation({ 0, 180, 0 });
	goLightPoint01->transform->SetWorldPosition({ distance, 1, distance });
	goLightPoint02->transform->SetWorldPosition({ distance, 1, -distance });
	goLightPoint03->transform->SetWorldPosition({ -distance, 1, distance });
	goLightPoint04->transform->SetWorldPosition({ -distance, 1, -distance });
	goLightSpot01->transform->SetWorldPosition({ distance / 2, 5, 0 });
	goLightSpot02->transform->SetWorldPosition({ -distance / 2, 5, 0 });

	//lightDir1->lightColor = { 1, 1, 1 };
	
	lightSpot1->transform->SetWorldRotation({ 0, 0, 90 });
	lightSpot2->transform->SetWorldRotation({ 0, 0, -90 });

	goLightPointArround01 = CreateGameObject("Point Arround 01");
	goLightPointArround01->transform->SetWorldPosition({0, 10, 0});
	PointLight* lightPointArround = CreatePointLight();
	goLightPointArround01->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 1, 0, 0 };

	goLightPointArround02 = CreateGameObject("Point Arround 02");
	goLightPointArround02->transform->SetWorldPosition({0, 20, 0});
	lightPointArround = CreatePointLight();
	goLightPointArround02->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 0, 1, 0 };

	goLightPointArround03 = CreateGameObject("Point Arround 03");
	goLightPointArround03->transform->SetWorldPosition({0, 30, 0});
	lightPointArround = CreatePointLight();
	goLightPointArround03->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 0, 0, 1 };

	goLightPointArround04 = CreateGameObject("Point Arround 04");
	goLightPointArround04->transform->SetWorldPosition({0, 40, 0});
	lightPointArround = CreatePointLight();
	goLightPointArround04->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 1, 0, 1 };

	GameObject* goLightPointStatic01 = CreateGameObject("Point Static 04");
	GameObject* goLightPointStatic02 = CreateGameObject("Point Static 04");
	GameObject* goLightPointStatic03 = CreateGameObject("Point Static 04");
	
	goLightPointStatic01->transform->SetWorldPosition({  2,  2 + 5, 45 });
	goLightPointStatic02->transform->SetWorldPosition({ -2,  2 + 5, 45 });
	goLightPointStatic03->transform->SetWorldPosition({  0, -2 + 5, 45 });
	
	
	float linear = -0.39f;
	lightPointArround = CreatePointLight();
	lightPointArround->lightColor = glm::vec3{ 1, 0, 0 };
	lightPointArround->linear = linear;
	goLightPointStatic01->AddComponent(lightPointArround);
	
	lightPointArround = CreatePointLight();
	lightPointArround->lightColor = glm::vec3{ 0, 1, 0 };
	lightPointArround->linear = linear;
	goLightPointStatic02->AddComponent(lightPointArround);
	
	lightPointArround = CreatePointLight();
	lightPointArround->lightColor = glm::vec3{ 0, 0, 1 };
	lightPointArround->linear = linear;
	goLightPointStatic03->AddComponent(lightPointArround);	
}

void Game::SetEnviroment()
{
	CreateSkybox("res/Skybox/Skybox_Right.jpg", "res/Skybox/Skybox_Left.jpg", "res/Skybox/Skybox_Top.jpg", "res/Skybox/Skybox_Bottom.jpg", "res/Skybox/Skybox_Front.jpg", "res/Skybox/Skybox_Back.jpg");
	float cubeDimensions = 50.0f;

	GameObject* worldContent = CreateGameObject("World Content");
	worldContent->transform->SetLocalPosition({ 0, 0, 0 });
	worldContent->transform->SetLocalScale({ 1, 1, 1 });
	worldContent->transform->SetLocalRotation({ 0, 0, 0 });

	GameObject* floor = CreateGameObject("Floor");
	Sprite* floorSprite = CreateSprite(CreateTexture("res/Layer2.png"));
	floor->AddComponent(floorSprite);
	floor->transform->SetLocalPosition({ 0, 0, 0 });
	floor->transform->SetLocalScale({ cubeDimensions * 4, cubeDimensions * 4, 1 });
	floor->transform->SetLocalRotation({ 90, 180, 0 });
	floorSprite->material->shininess = 10000;
	floorSprite->material->specular = {0, 0, 0};
	floorSprite->material->diffuse = {0.5f, 0.5f, 0.5f };
	
	GameObject* wallRight = CreateGameObject("Wall Right");
	wallRight->transform->SetParent(worldContent);
	wallRight->AddComponent(CreateSprite(CreateTexture("res/World/Right.png")));
	wallRight->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0.01f });
	wallRight->transform->SetLocalPosition({ cubeDimensions, cubeDimensions / 2, 0 });
	wallRight->transform->SetLocalRotation({ 0, -90, 0 });

	GameObject* wallLeft = CreateGameObject("Wall Left");
	wallLeft->transform->SetParent(worldContent);
	wallLeft->AddComponent(CreateSprite(CreateTexture("res/World/Left.png")));
	wallLeft->transform->SetLocalPosition({ -cubeDimensions, cubeDimensions / 2, 0 });
	wallLeft->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallLeft->transform->SetLocalRotation({ 0, 90, 0 });

	GameObject* wallBack = CreateGameObject("Wall Back");
	wallBack->transform->SetParent(worldContent);
	wallBack->AddComponent(CreateSprite(CreateTexture("res/World/Back.png")));
	wallBack->transform->SetLocalPosition({ 0, cubeDimensions / 2, cubeDimensions });
	wallBack->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallBack->transform->SetLocalRotation({ 0, 180, 0 });

	Texture* front = CreateTexture("res/World/Front.png");
	Sprite* spriteFront = CreateSprite(front);
	GameObject* wallFront = CreateGameObject("Wall Front");
	wallFront->transform->SetParent(worldContent);
	wallFront->AddComponent(spriteFront);
	wallFront->transform->SetLocalPosition({ 0, cubeDimensions / 2, -cubeDimensions });
	wallFront->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });

	// 4 Cubes
	cubeContent = CreateGameObject("Cube Content");
	cubeContent->transform->SetWorldScale({ 10, 10, 10 });
	cubeContent->transform->SetWorldPosition({ 0, 5, 0 });

	GameObject* cube1 = CreateGameObject("Cube 1");
	cube1->transform->SetParent(cubeContent);
	Cube* cubeWithTexture = CreateCube();
	cubeWithTexture->SetTexture(CreateTexture("res/Layer9.png"));
	cube1->AddComponent(cubeWithTexture);

	GameObject* cube2 = CreateGameObject("Cube 2");
	cube2->transform->SetParent(cubeContent);
	cube2->AddComponent(CreateCube());

	GameObject* cube3 = CreateGameObject("Cube 3");
	cube3->transform->SetParent(cubeContent);
	cube3->AddComponent(CreateCube());

	GameObject* cube4 = CreateGameObject("Cube 4");
	cube4->transform->SetParent(cubeContent);
	cube4->AddComponent(CreateCube());
	
	float distance = 2;
	cube1->transform->SetLocalPosition({ distance, 0, distance });
	cube2->transform->SetLocalPosition({ distance, 0, -distance });
	cube3->transform->SetLocalPosition({ -distance, 0, distance });
	cube4->transform->SetLocalPosition({ -distance, 0, -distance });
	//cube4->SetActive(false);
	
	// Sprite Goku
	Texture* miniGokuTexture = CreateTexture("res/Goku.png");
	objectFoward = CreateGameObject("miniGoku3");
	objectFoward->AddComponent(CreateSprite(miniGokuTexture));
	objectFoward->transform->SetLocalScale({ 10, 10, 1 });
	objectFoward->transform->SetLocalScale({ 10, 10, 1 });
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
	player->transform->SetWorldPosition(glm::vec3(0, 10, 0));

	player->visualPlayer->AddComponent(CreateCube());
	
	GameObject* spotGo = CreateGameObject("SpotLight Player");
	spotGo->AddComponent(CreateSpotLight());
	spotGo->transform->SetParent(player->pivot);
}

void Game::AddMinimap()
{
	GameObject* cameraMinimapGo = CreateGameObject("Camera MiniMap");
	cameraMinimapGo->transform->SetWorldPosition({ -50, 10, 50 });
	cameraMinimapGo->transform->SetWorldRotation({ -90, 0, 0 });
	Camera* cameraMinimap = CreateCamera({ 0, 720 - 200 }, { 200, 200 }, Camera::Orthogonal, true);
	cameraMinimap->SetZoom(2.0f);
	cameraMinimapGo->AddComponent(cameraMinimap);
}

void Game::AddModels3D()
{
	GameObject* backpackObject = CreateGameObject("BackPack");
	backpackObject->transform->SetWorldScale({ 2, 2, 2 });
	backpackObject->transform->SetWorldPosition({ 0, 5, 0 });
	Model* modelBackPack = CreateModel("res/Backpack/backpack.obj", true, true);
	backpackObject->AddComponent(modelBackPack);

	GameObject* modelJakeObject = CreateGameObject("Jake Model");
	modelJakeObject->transform->SetWorldScale({ 0.5f, 0.5f, 0.5f });
	modelJakeObject->transform->SetWorldPosition({ -10, 5, 0 });
	Model* modelJake = CreateModel("res/Jake/Jake_Test1.obj", true, false);
	modelJakeObject->AddComponent(modelJake);

	GameObject* modelGokuObject = CreateGameObject("Goku Model");
	modelGokuObject->transform->SetWorldScale({ 10, 10, 10 });
	modelGokuObject->transform->SetWorldPosition({ 10, 5, 0 });
	Model* modelGoku = CreateModel("res/Goku/A.obj", true, false);
	modelGokuObject->AddComponent(modelGoku);
}

void Game::OnMouseMove(double xPos, double yPos)
{
	//std::cout << "Mouse Pos: {" << xPos << ", " << yPos << "}\n";
}

void Game::OnMouseScrollMovement(double xOffset, double yOffset)
{

	//std::cout << "Mouse Scroll: {" << xOffset << ", " << yOffset << "}\n";
}

void Game::DeInitialize()
{

}