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
#include "../../Time.h"

using namespace std;

class SAUCA_API BaseGame
{
private:
	Input* input;
	Window* window;
	Renderer* renderer;
	CollisionManager* collisionManager;
	Time* timer;

	void BeforeDraw();
	void AfterDraw();
public:
	BaseGame();
	~BaseGame();
	int Init();

	// User Interface
	virtual void Initialize() = 0;
	virtual void Inputs() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DeInitialize() = 0;

	// World Objects
	Triangle* CreateTriangle();
	Quad* CreateQuad();
	Sprite* CreateSprite(Texture* texture);
	void SetMaterial(Material* material);

	// Inputs
	bool IsKeyReleased(KeyCode keyCode);
	bool IsKeyDown(KeyCode keyCode);
	bool IsKeyPressed(KeyCode keyCode);
	int GetKey();

	// Time
	double DeltaTime();
	double ElapsedTime();
};
	
#endif