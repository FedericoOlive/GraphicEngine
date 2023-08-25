#include "BaseGame.h"

#include "Render/BinarySpacePartitioning.h"
#include "Utility/PrintInConsole.h"

string BaseGame::version = "2.3.0";
Event<> BaseGame::OnUpdateEvent;
Event<> BaseGame::OnInputEvent;

void BaseGame::BeforeDraw()
{
	renderer->Clear(GL_COLOR_BUFFER_BIT);
}

void BaseGame::AutoDraw()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (skybox != nullptr)
		skybox->Draw(Renderer::cameras);
	renderer->Draw();
	//DrawCollision();
}

void BaseGame::AfterDraw()
{
	renderer->SwapBuffers(window->GetWindow());
}

void BaseGame::LoadInfo()
{
	int width = 0, height = 0;
	glfwGetWindowSize(window->GetWindow(), &width, &height);
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	string dataTab = "Data: \t > ";
	std::cout << "Data: Initialize SauCa " << version << "\n";
	std::cout << dataTab << "Display Size:    " << width << " x " << height << "\n";
	std::cout << dataTab << "Screen Size:     " << mode->width << " x " << mode->height << "\n";
	std::cout << dataTab << "Render Size:     " << mode->width << " x " << mode->height << "\n";
	std::cout << dataTab << "Viewport Offset: " << "0, 0" << "\n";
	std::cout << "\n";

	std::cout << "Data: OpenGL device information:\n";
	std::cout << dataTab << "Device:   " << glGetString(GL_VENDOR) << "\n";
	std::cout << dataTab << "Version:  " << glGetString(GL_VERSION) << "\n";
	std::cout << dataTab << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << dataTab << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	std::cout << "\n";
}

BaseGame::BaseGame()
{
	input = nullptr;
	window = nullptr;
	renderer = nullptr;
	collisionManager = new CollisionManager();
	collisionManager3D = new CollisionManager3D();
	timer = nullptr;
}

BaseGame::~BaseGame()
{

}

int BaseGame::Init()
{
#ifdef _DEBUG
	PrintInConsole::SetConsolePosition(300, 25);
#endif

	window = new Window();
	renderer = new Renderer();
	input = new Input();
	timer = new Timer();

	window->InitLibrary();
	window->CreateWindow();
	window->CheckWindow(window->GetWindow());
	window->AssignContext(window->GetWindow());
	renderer->CreateRenderer();

	LoadInfo();

	renderer->CreateShader();
	input->InitInput(window);

	// glfwSwapInterval(0);
	Initialize();
	while (!window->WindowShouldClose(window->GetWindow()))
	{
		//if (timer->IsEndCounter())
		//    window->AddStringToNameWindow(timer->GetTimeInfo());

		window->PollEvents();

		timer->Update();

		OnInputEvent.Invoke();
		Inputs();

		OnUpdateEvent.Invoke();
		Update();

		//collisionManager->UpdateCollisions();
		collisionManager3D->UpdateCollisions();

		BeforeDraw();
		AutoDraw();
		Draw();
		AfterDraw();
	}

	DeInitializeEngine();
	DeInitialize();

	window->TerminateLibrary();
	return 0;
}

void BaseGame::DeInitializeEngine()
{
	while (!gameobjects.empty())
	{
		auto gameObject = gameobjects.begin();

		if ((*gameObject)->transform->parent == nullptr)
		{
			std::list<Transform*> allChildrens;
			(*gameObject)->transform->GetRecursivelyChildrens(allChildrens);
			while (!allChildrens.empty())
			{
				auto childtransform = allChildrens.begin();
				gameobjects.remove((*childtransform)->gameObject);
				allChildrens.pop_front();
			}

			delete (*gameObject);
			(*gameObject) = nullptr;
		}

		gameobjects.pop_front();
	}

	if (skybox != nullptr)
	{
		delete skybox;
		skybox = nullptr;
	}
	if (input != nullptr)
	{
		delete input;
		input = nullptr;
	}
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
	if (collisionManager != nullptr)
	{
		delete collisionManager;
		collisionManager = nullptr;
	}
	if (collisionManager3D != nullptr)
	{
		delete collisionManager3D;
		collisionManager3D = nullptr;
	}
	if (timer != nullptr)
	{
		delete timer;
		timer = nullptr;
	}
}

GameObject* BaseGame::CreateGameObject(string name)
{
	GameObject* gameObject = new GameObject(name);
	gameobjects.push_back(gameObject);
	Renderer::AddToRenderList(gameObject);
	return gameObject;
}

Triangle* BaseGame::CreateTriangle()
{
	Triangle* triangle = new Triangle(renderer);
	return triangle;
}

Quad* BaseGame::CreateQuad()
{
	Quad* quad = new Quad(renderer);
	return quad;
}

Quad* BaseGame::CreateQuad(Material* mat)
{
	Quad* quad = new Quad(renderer, mat);
	return quad;
}

Sprite* BaseGame::CreateSprite(Texture* texture)
{
	Sprite* sprite = new Sprite(texture, renderer);
	return sprite;
}

Cube* BaseGame::CreateCube()
{
	Cube* cube = new Cube(renderer);
	return cube;
}

Cube* BaseGame::CreateCube(Material* mat)
{
	Cube* cube = new Cube(renderer, mat);	
	return cube;
}

Texture* BaseGame::CreateTexture(string path)
{
	Texture* texture = new Texture(path);
	return texture;
}

void BaseGame::CreateSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back)
{
	std::vector<std::string> faces
	{
		right,
		left,
		top,
		bottom,
		front,
		back
	};
	skybox = new Skybox(renderer, faces);
}

Camera* BaseGame::CreateCamera(glm::vec2 viewportPosition, glm::vec2 viewportSize, Camera::CameraType cameraType, bool autoAddGameObjects)
{
	Camera* camera = new Camera(viewportPosition, viewportSize, cameraType);
	camera->autoAddGameObjects = autoAddGameObjects;
	renderer->AddCamera(camera);
	return camera;
}

Model* BaseGame::CreateModel(string path, bool isInvertIndexesOrder, bool IsInvertTextures)
{
	Model* newModel = new Model(renderer, path, isInvertIndexesOrder, IsInvertTextures);//FileSystem::getPath("resources/objects/backpack/backpack.obj"));
	return newModel;
}

CharacterController* BaseGame::CreateCharacterController(Camera* camera)
{
	GameObject* root = CreateGameObject("Player");
	GameObject* cameraPivot = CreateGameObject("Camera Pivot");
	GameObject* cameraGameObject = CreateGameObject("Camera GameObject");
	GameObject* visualPlayer = CreateGameObject("Visual");
	CharacterController* characterController = new CharacterController(root, visualPlayer, cameraPivot, cameraGameObject, camera);
	return characterController;
}

DirectionalLight* BaseGame::CreateDirectionalLight()
{
	DirectionalLight* dirLight = new DirectionalLight(renderer);
	renderer->directionalLights.push_back(dirLight);
	return dirLight;
}

PointLight* BaseGame::CreatePointLight()
{
	PointLight* pointLight = new PointLight(renderer);
	renderer->pointLights.push_back(pointLight);
	return pointLight;
}

SpotLight* BaseGame::CreateSpotLight()
{
	SpotLight* spotLight = new SpotLight(renderer);
	renderer->spotLights.push_back(spotLight);
	return spotLight;
}

void BaseGame::AddCollision(Entity2D* entity, bool isStatic)
{
	collisionManager->AddToCollisionList(entity, isStatic);
}

void BaseGame::UpdateCollisions(TileMap* tileMap)
{
	collisionManager->UpdateCollisionsInTileMap(tileMap);
}

void BaseGame::DrawCollision()
{
	for (Collider*& collider : collisionManager3D->dynamicCollisionList)
	{
		DrawCubeLines(collider->transform->aabbGlobal, collider->lineWidth, collider->color);
	}

	for (Collider*& collider : collisionManager3D->staticCollisionList)
	{
		DrawCubeLines(collider->transform->aabbGlobal, collider->lineWidth, collider->color);
	}
}

void BaseGame::DrawCubeLines(AABB* aabb, float lineWidth, glm::vec3 color, Camera* camera)
{
	Renderer::DrawCubeLines(aabb, lineWidth, color, camera);
}

void BaseGame::DrawLine(const glm::vec3& startPoint, const glm::vec3& endPoint, float lineWidth, glm::vec3 color, Camera* camera)
{
	renderer->DrawLine(startPoint, endPoint, lineWidth, color, camera);
}

Collider* BaseGame::CreateCollider(bool isStatic)
{
	Collider* collider = new Collider();
	collisionManager3D->AddToCollisionList(collider, isStatic);
	return collider;
}

TileMap* BaseGame::CreateTileMap(string filePath, string resPath)
{
	TileMap* tileMap = new TileMap(renderer);
	if (tileMap->ImportTileMap(filePath, resPath))
	{
		cout << "TileMap load successfully.\n";
	}
	else
	{
		cout << "TileMap can not load.\n";
	}
	return tileMap;
}

void BaseGame::ShowHierarchyInConsole()
{
	PrintInConsole::PrintHierarchyInConsole(gameobjects);
}

double BaseGame::DeltaTime()
{
	return Timer::DeltaTime();
}

double BaseGame::ElapsedTime()
{
	return timer->ElapsedTime();
}

void BaseGame::CreateBinarySpacePartitioning(Transform* target)
{
	BinarySpacePartitioning::isEnable = true;
	BinarySpacePartitioning::SetTarget(target);
}

void BaseGame::AddPlaneBSP(Transform* plane)
{
	BinarySpacePartitioning::AddPlane(plane);
}
