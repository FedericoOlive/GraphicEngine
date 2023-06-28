#include "Game.h"
#include <time.h>


void Game::Initialize()
{
	camera = CreateCamera({ 0,0 }, { 1280, 720 }, Camera::Perspective, true);
	
	targetFloatModify = &multiply;
	AddModels3D();
	SetLights();
	AddListeners();
	AddPlayer();
	AddMinimap();
	SetEnviroment();
	
	target = cubeContent->transform;
}

void Game::Inputs()
{
	if (Input::IsKeyDown(KeyCode::Kp0)) { targetFloatModify = &multiply;							targetString = "multiply: ";		cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp1)) { targetFloatModify = &(spotlightPlayer->constant);			targetString = "constant: ";		cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp2)) { targetFloatModify = &(spotlightPlayer->linear);			targetString = "linear: ";			cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp3)) { targetFloatModify = &(spotlightPlayer->quadratic);		targetString = "quadratic: ";		cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp4)) { targetFloatModify = &(spotlightPlayer->cutOff);			targetString = "cutOff: ";			cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp5)) { targetFloatModify = &(spotlightPlayer->outerCutOff);		targetString = "outerCutOff: ";		cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp6)) { targetFloatModify = &(spotlightPlayer->powerAmbient);		targetString = "powerAmbient: ";	cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp7)) { targetFloatModify = &(spotlightPlayer->powerDiffuse);		targetString = "powerDiffuse: ";	cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp8)) { targetFloatModify = &(spotlightPlayer->powerSpecular);	targetString = "powerSpecular: ";	cout << "Get: " << targetString << "\n";	}
	if (Input::IsKeyDown(KeyCode::Kp9)) { ChangeColorSpotLight(); }
	
	if (Input::IsKeyHolding(KeyCode::Q)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3( 1 * multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::E)) { target->SetLocalPosition(target->GetLocalPosition() + glm::vec3(-1 * multiply, 0, 0)); }
	if (Input::IsKeyHolding(KeyCode::Z)) { *targetFloatModify -= 1.01f; cout << targetString << (*targetFloatModify) << "\n"; }
	if (Input::IsKeyHolding(KeyCode::X)) { *targetFloatModify += 1.01f; cout << targetString << (*targetFloatModify) << "\n"; }
	if (Input::IsKeyDown(KeyCode::P)) { rotatePlanets = !rotatePlanets; }
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
	
	if (rotatePlanets)
	{
		timeRotation += Timer::DeltaTime();
		sol->transform->SetLocalRotation(glm::vec3{ 0, (timeRotation * 360) / 10, 0 });
		tie->transform->SetLocalRotation(glm::vec3{ 0, (timeRotation * 360) /  5, 0 });
		lun->transform->SetLocalRotation(glm::vec3{ 0, (timeRotation * 360) / 20, 0 });
	}

	//objectFoward->transform->SetWorldPosition(cubeContent->transform->GetWorldPosition() + cubeContent->transform->forward() * 2.0f + glm::vec3{ 0, 5, 0 });

	goLightPointArround01->transform->SetWorldPosition(glm::vec3{ glm::sin(time * 0.2f) * 45, 10, glm::cos(time * 0.2f) * 45 });
	goLightPointArround02->transform->SetWorldPosition(glm::vec3{ glm::sin(time * 0.4f) * 45, 15, glm::cos(time * 0.4f) * 45 });
	goLightPointArround03->transform->SetWorldPosition(glm::vec3{ glm::sin(time * 0.8f) * 45, 20, glm::cos(time * 0.8f) * 45 });
	goLightPointArround04->transform->SetWorldPosition(glm::vec3{ glm::sin(time * 1.6f) * 45, 25, glm::cos(time * 1.6f) * 45 });
}

void Game::Draw()
{
	//DrawLine({ 0, 0, 0 }, cube2->transform->GetWorldPosition());
	//DrawCubeLines(cube1->transform->aabb, 2, {1, 0, 0}, camera);
	//DrawCubeLines(cube2->transform->aabb, 2, {0, 1, 0}, camera);
	//DrawCubeLines(cube3->transform->aabb, 2, {0, 0, 1}, camera);
	DrawCubeLines(cubeContent->transform->aabbGlobal, 2, Color::Blue, camera);
	DrawCubeLines(cubeContent->transform->aabbGlobal, 2, Color::Blue, cameraMinimap);
}

void Game::SetLights()
{
	GameObject* goLightDir01 = CreateGameObject("Dir Light 1");
	goLightDir01->transform->SetWorldRotation({ -45, 0, 0 });
	//GameObject* goLightDir02 = CreateGameObject("Dir Light 2");
	GameObject* goLightPoint01 = CreateGameObject("Point Light 1");
	GameObject* goLightPoint02 = CreateGameObject("Point Light 2");
	GameObject* goLightPoint03 = CreateGameObject("Point Light 3");
	GameObject* goLightPoint04 = CreateGameObject("Point Light 4");
	GameObject* goLightSpot01 = CreateGameObject("Spot Light 1");
	GameObject* goLightSpot02 = CreateGameObject("Spot Light 2");

	DirectionalLight* lightDir1 = CreateDirectionalLight();
	lightDir1->powerDiffuse = 2;
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
	goLightDir01->transform->SetWorldPosition({ 0, 100, 0 });
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
	float powerLight = 4;
	goLightPointArround01 = CreateGameObject("Point Arround 01");
	goLightPointArround01->transform->SetWorldPosition({0, 10, 0});
	PointLight* lightPointArround = CreatePointLight();
	goLightPointArround01->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 1, 0, 0 };
	lightPointArround->powerAmbient = powerLight;
	lightPointArround->powerDiffuse = powerLight;

	goLightPointArround02 = CreateGameObject("Point Arround 02");
	goLightPointArround02->transform->SetWorldPosition({0, 20, 0});
	lightPointArround = CreatePointLight();
	goLightPointArround02->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 0, 1, 0 };
	lightPointArround->powerAmbient = powerLight;
	lightPointArround->powerDiffuse = powerLight;

	goLightPointArround03 = CreateGameObject("Point Arround 03");
	goLightPointArround03->transform->SetWorldPosition({0, 30, 0});
	lightPointArround = CreatePointLight();
	goLightPointArround03->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 0, 0, 1 };
	lightPointArround->powerAmbient = powerLight;
	lightPointArround->powerDiffuse = powerLight;

	goLightPointArround04 = CreateGameObject("Point Arround 04");
	goLightPointArround04->transform->SetWorldPosition({0, 40, 0});
	lightPointArround = CreatePointLight();
	goLightPointArround04->AddComponent(lightPointArround);
	lightPointArround->lightColor = glm::vec3{ 1, 0, 1 };
	lightPointArround->powerAmbient = powerLight;
	lightPointArround->powerDiffuse = powerLight;

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

	// Sprite Goku
	Texture* miniGokuTexture = CreateTexture("res/Goku.png");
	objectFoward = CreateGameObject("miniGoku3");
	Sprite* miniGokuSprite = CreateSprite(miniGokuTexture);
	objectFoward->AddComponent(miniGokuSprite);
	objectFoward->AddComponent(CreateCollider());
	objectFoward->transform->SetLocalScale({ 10, 10, 1 });

	GameObject* worldContent = CreateGameObject("World Content");
	worldContent->transform->SetLocalPosition({ 0, 0, 0 });
	worldContent->transform->SetLocalScale({ 1, 1, 1 });
	worldContent->transform->SetLocalRotation({ 0, 0, 0 });

	GameObject* floor = CreateGameObject("Floor");
	Sprite* floorSprite = CreateSprite(CreateTexture("res/Layer2.png"));
	floor->AddComponent(floorSprite);
	floor->transform->SetLocalPosition({ 0, 0, 0 });
	floor->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	floor->transform->SetLocalRotation({ 90, 180, 0 });
	floorSprite->material->shininess = 10000;
	floorSprite->material->specular = { 0, 0, 0 };
	floorSprite->material->diffuse = { 0.5f, 0.5f, 0.5f };

	GameObject* wallRight = CreateGameObject("Wall Right");
	wallRight->transform->SetParent(worldContent);
	wallRight->AddComponent(CreateSprite(CreateTexture("res/World/Right.png")));
	wallRight->transform->SetLocalPosition({ cubeDimensions, cubeDimensions, 0 });
	wallRight->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 0.01f });
	wallRight->transform->SetLocalRotation({ 0, -90, 0 });
	wallRight->AddComponent(CreateCollider());

	GameObject* wallLeft = CreateGameObject("Wall Left");
	wallLeft->transform->SetParent(worldContent);
	wallLeft->AddComponent(CreateSprite(CreateTexture("res/World/Left.png")));
	wallLeft->transform->SetLocalPosition({ -cubeDimensions, cubeDimensions, 0 });
	wallLeft->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallLeft->transform->SetLocalRotation({ 0, 90, 0 });
	wallLeft->AddComponent(CreateCollider());

	GameObject* wallBack = CreateGameObject("Wall Back");
	wallBack->transform->SetParent(worldContent);
	wallBack->AddComponent(CreateSprite(CreateTexture("res/World/Back.png")));
	wallBack->transform->SetLocalPosition({ 0, cubeDimensions, cubeDimensions });
	wallBack->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallBack->transform->SetLocalRotation({ 0, 180, 0 });
	wallBack->AddComponent(CreateCollider());

	Texture* front = CreateTexture("res/World/Front.png");
	Sprite* spriteFront = CreateSprite(front);
	GameObject* wallFront = CreateGameObject("Wall Front");
	wallFront->transform->SetParent(worldContent);
	wallFront->AddComponent(spriteFront);
	wallFront->transform->SetLocalPosition({ 0, cubeDimensions, -cubeDimensions });
	wallFront->transform->SetLocalScale({ cubeDimensions * 2, cubeDimensions * 2, 1 });
	wallFront->transform->SetLocalRotation({ 0, 0, 0 });
	wallFront->AddComponent(CreateCollider());

	// 4 Cubes
	cubeContent = CreateGameObject("Cube Content");

	float distance = 2;

	cube1 = CreateGameObject("Cube 1");
	cube1->transform->SetParent(cubeContent);
	cube1->transform->SetWorldPosition({ distance, 0, distance });
	Cube* cube1CubeComponent = CreateCube();
	cube1CubeComponent->SetTexture(CreateTexture("res/Layer9.png"));
	cube1->AddComponent(cube1CubeComponent);
	Collider* col1 = CreateCollider();
	cube1->AddComponent(col1);

	cube2 = CreateGameObject("Cube 2");
	cube2->transform->SetParent(cubeContent);
	cube2->transform->SetWorldPosition({ distance, 0, -distance });
	Cube* cube2CubeComponent = CreateCube();
	cube2->AddComponent(cube2CubeComponent);
	Collider* col2 = CreateCollider();
	cube2->AddComponent(col2);

	cube3 = CreateGameObject("Cube 3");
	cube3->transform->SetParent(cubeContent);
	cube3->transform->SetWorldPosition({ -distance, 0, distance });
	Cube* cube3CubeComponent = CreateCube();
	cube3->AddComponent(cube3CubeComponent);
	Collider* col3 = CreateCollider();
	cube3->AddComponent(col3);

	cube4 = CreateGameObject("Cube 4");
	cube4->transform->SetParent(cubeContent);
	cube4->transform->SetWorldPosition({ -distance, 0, -distance });
	Cube* cube4CubeComponent = CreateCube();
	cube4->AddComponent(cube4CubeComponent);
	Collider* col4 = CreateCollider();
	cube4->AddComponent(col4);

	cube4CubeComponent->SetColorTint(81 / 255.0f, 209 / 255.0f, 246 / 255.0f, 0.5f);

	//cubeMovement = new EntityController();
	//cubeMovement->RemoveRotation();
	//cubeMovement->SetSpeedMovements(0.1f);
	//cube2->AddComponent(cubeMovement);

	cubeContent->transform->SetWorldScale({ 10, 10, 10 });
	cubeContent->transform->SetWorldPosition({ 0, 5, 0 });


	
	sol = CreateGameObject("Cube XX");
	sol->transform->SetWorldPosition({ 0, 30,  0 });
	Cube* cube = CreateCube();
	sol->AddComponent(cube);
	cube->material->colorTint = Color::Red;
	Collider* col = CreateCollider();
	sol->AddComponent(col);

	tie = CreateGameObject("Cube XX");
	tie->transform->SetParent(sol);
	tie->transform->SetWorldPosition({ 0, 30, 20 });
	cube = CreateCube();
	cube->material->colorTint = Color::Green;
	tie->AddComponent(cube);
	col = CreateCollider();
	tie->AddComponent(col);

	lun = CreateGameObject("Cube XX");
	lun->transform->SetParent(tie);
	lun->transform->SetWorldPosition({ 0, 30, 25 });
	cube = CreateCube();
	cube->material->colorTint = Color::Blue;
	lun->AddComponent(cube);
	col = CreateCollider();
	lun->AddComponent(col);
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
	player->transform->SetWorldPosition(glm::vec3(0, 10, 0));
	
	player->visualPlayer->AddComponent(CreateCube());
	
	GameObject* spotGo = CreateGameObject("SpotLight Player");
	spotlightPlayer = CreateSpotLight();
	spotGo->AddComponent(spotlightPlayer);
	spotGo->transform->SetParent(player->pivot);

	Collider* col = CreateCollider(false);
	player->transform->gameObject->AddComponent(col);
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

Model* Game::AddNewModel(std::string name, std::string path, glm::vec3 pos)
{
	float modelScale = 0.07f;
	GameObject* newModelGameObject = CreateGameObject(name);
	newModelGameObject->transform->SetWorldScale({ modelScale, modelScale, modelScale });
	newModelGameObject->transform->SetWorldPosition(pos);
	newModelGameObject->AddComponent(CreateCollider(false));
	Model* newModel = CreateModel(path, true);
	newModelGameObject->AddComponent(newModel);
	return newModel;
}

void Game::AddModels3D()
{
	Model* modelVampire = AddNewModel("Vampire", "res/Vampire/Vampire A Lusth.dae", {0, 0, -20});
	Model* modelArcher = AddNewModel("Archer", "res/Archer/Archer.dae", {-20, 0, 0});
	modelArcher->transform->SetWorldRotation({ 0, 90, 0 });
	Model* modelMaria = AddNewModel("Maria", "res/Maria/Maria.dae", {20, 0, 0});
	modelMaria->transform->SetWorldRotation({ 0, -90, 0 });
	
	//GameObject* backpackObject = CreateGameObject("BackPack");
	//backpackObject->transform->SetWorldScale({ 2, 2, 2 });
	//backpackObject->transform->SetWorldPosition({ 0, 5, 0 });
	//Model* modelBackPack = CreateModel("res/Backpack/backpack.obj", true, true);
	//backpackObject->AddComponent(modelBackPack);
	//
	
	GameObject* modelJakeObject = CreateGameObject("Jake Model");
	modelJakeObject->transform->SetWorldScale({ 0.5f, 0.5f, 0.5f });
	modelJakeObject->transform->SetWorldPosition({ -10, 5, 5 });
	modelJakeObject->transform->SetWorldRotation({ 0, 180, 0 });
	Model* modelJake = CreateModel("res/Jake/Jake_Test1.obj", true, false);
	modelJakeObject->AddComponent(modelJake);
	modelJakeObject->AddComponent(CreateCollider(false));
	// Set as Gold
	modelJake->material->ambient = { 0.24725f, 0.1995f, 0.0745f };
	modelJake->material->diffuse = { 0.75164f, 0.60648f, 0.22648f };
	modelJake->material->specular = { 0.628281f, 0.555802f, 0.366065f };
	modelJake->material->shininess = 0.4f * 128.0f;

	GameObject* modelJakeObject2 = CreateGameObject("Jake Model");
	modelJakeObject2->transform->SetWorldScale({ 1, 1, 1 });
	modelJakeObject2->transform->SetWorldPosition({ -20, 0, -20 });
	Model* modelJake2 = CreateModel("res/Jake/Jake_Test1.obj", true, false);
	modelJakeObject2->AddComponent(modelJake2);
	modelJakeObject2->AddComponent(CreateCollider(false));
	// Set as Normal
	modelJake2->material->ambient = { 1, 1, 1 };
	modelJake2->material->diffuse = { 1, 1, 1 };
	modelJake2->material->specular ={ 1, 1, 1 };
	modelJake2->material->shininess = 128.0f;
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

void Game::DeInitialize()
{

}