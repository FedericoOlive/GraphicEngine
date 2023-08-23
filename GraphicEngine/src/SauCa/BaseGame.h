#ifndef BASEGAME_H
#define BASEGAME_H

#include "Exports.h"
#include <iostream>
#include "CollisionManager.h"
#include "Renderer.h"
#include "Window.h"
#include "Entity/Entity2D/Triangle.h"
#include "Entity/Entity2D/Sprite.h"
#include "Entity/Entity2D/Quad.h"
#include "Input/Input.h"
#include "Timer.h"
#include "Entity/Entity2D/Skybox.h"
#include "Entity/Entity2D/TileMap.h"
#include "Entity/Entity3D/Cube.h"
#include "Entity/Entity3D/Model.h"
#include "Light/DirectionalLight.h"
#include "Movement/CharacterController.h"
#include "Render/Camera.h"
#include "Utility/Event.h"
#include "Collision/CollisionManager3D.h"
#include "Utility/Color.h"

using namespace std;

class SAUCA_API BaseGame
{
private:
	static string version;

	Input* input;
	Window* window;
	Renderer* renderer;
	CollisionManager* collisionManager;
	CollisionManager3D* collisionManager3D;
	Timer* timer;
	list<GameObject*> gameobjects;
	Skybox* skybox;

	void BeforeDraw();
	void AutoDraw();
	void AfterDraw();

	void LoadInfo();

public:
	static Event<> OnUpdateEvent;
	static Event<> OnInputEvent;

	BaseGame();
	~BaseGame();
	int Init();
	void DeInitializeEngine();

	// User Interface
	virtual void Initialize() = 0;
	virtual void Inputs() = 0;
	virtual void Update() = 0;
	virtual void DeInitialize() = 0;
	virtual void Draw() = 0;

	// World Components
	GameObject* CreateGameObject(string name = "");
	Triangle* CreateTriangle();
	Quad* CreateQuad();
	Quad* CreateQuad(Material* mat);
	Sprite* CreateSprite(Texture* texture);
	Cube* CreateCube();
	Texture* CreateTexture(string path);
	void CreateSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	Camera* CreateCamera(glm::vec2 viewportPosition = { 0, 0 }, glm::vec2 viewportSize = { 1280, 720 }, Camera::CameraType cameraType = Camera::CameraType::Perspective, bool autoAddGameObjects = true);
	Model* CreateModel(string path, bool isInvertIndexesOrder = false, bool IsInvertTextures = false);
	CharacterController* CreateCharacterController(Camera* camera);

	// Lights
	DirectionalLight* CreateDirectionalLight();
	PointLight* CreatePointLight();
	SpotLight* CreateSpotLight();

	//Collisions
	void AddCollision(Entity2D* entity, bool isStatic);
	void UpdateCollisions(TileMap* tileMap);
	void DrawCollision();
	void DrawCubeLines(AABB* aabb, float lineWidth = 2, glm::vec3 color = { 0, 0, 0 }, Camera* camera = nullptr);
	void DrawLine(const glm::vec3& startPoint, const glm::vec3& endPoint, float lineWidth = 2.0f, glm::vec3 color = { 1, 0, 0 }, Camera* camera = nullptr);
	Collider* CreateCollider(bool isStatic = true);

	// Utilities
	TileMap* CreateTileMap(string filePath, string resPath);
	void ShowHierarchyInConsole();

	// Time
	double DeltaTime();
	double ElapsedTime();

	// Window
	void LockCursor(bool isEnable) { window->LockCursor(isEnable); }

	// BSP
	void CreateBinarySpacePartitioning(Transform* target);
	void AddPlaneBSP(Transform* plane);
};

#endif