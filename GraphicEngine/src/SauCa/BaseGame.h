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
#include "Light/DirectionalLight.h"
#include "Render/Camera.h"
#include "Utility/Event.h"
#include "Movement/CharacterController.h"

using namespace std;

class SAUCA_API BaseGame
{
private:
	static string version;
		
	Input* input;
	Window* window;
	Renderer* renderer;
	CollisionManager* collisionManager;
	Timer* timer;
	list<GameObject*> gameobjects;
	Skybox* skybox;
	
	void BeforeDraw();
	void Draw();
	void AfterDraw();

	void LoadInfo();
	void ShowHierarchyInConsole(Transform* transf, string preText);

public:
	static Event<> OnUpdateEvent;
	static Event<> OnInputEvent;
	BaseGame();
	~BaseGame();
	int Init();

	// User Interface
	virtual void Initialize() = 0;
	virtual void Inputs() = 0;
	virtual void Update() = 0;
	virtual void DeInitialize() = 0;

	// World Objects
	Triangle* CreateTriangle();
	Quad* CreateQuad();
	Quad* CreateQuad(Material* mat);
	Sprite* CreateSprite(Texture* texture);
	Cube* CreateCube();
	void CreateSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	GameObject* CreateGameObject(string name = "");
	Camera* CreateCamera(glm::vec2 viewportPosition = { 0, 0 }, glm::vec2 viewportSize = { 1280, 720 }, Camera::CameraType cameraType = Camera::CameraType::Perspective, bool autoAddGameObjects = true);
	

	// Lights
	DirectionalLight* CreateDirectionalLight();
	PointLight* CreatePointLight();
	SpotLight* CreateSpotLight();
	
	//Collisions
	void AddCollision(Entity2D* entity, bool isStatic);
	void UpdateCollisions(TileMap* tileMap);
	
	// Utilities
	TileMap* CreateTileMap(string filePath, string resPath);
	void ShowHierarchyInConsole() const;

	// Inputs
	bool IsKeyReleased(KeyCode keyCode);
	bool IsKeyDown(KeyCode keyCode);
	bool IsKeyPressed(KeyCode keyCode);
	int GetKey();

	// Time
	double DeltaTime();
	double ElapsedTime();

	// Window
	void ModifyWindow(const char* name, float width, float height);
	void LockCursor(bool isEnable) { window->LockCursor(isEnable); }

	
};
	
#endif