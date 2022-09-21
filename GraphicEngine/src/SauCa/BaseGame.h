#ifndef BASEGAME_H
#define BASEGAME_H

#include "Exports.h"
#include <iostream>
#include "Input.h"
#include "CollisionManager.h"
#include "Renderer.h"
#include "Window.h"
#include "Entity/Entity2D/Triangle.h"

using namespace std;

class SAUCA_API BaseGame
{
private:
	Input* input;
	Window* window;
	Renderer* renderer;
	CollisionManager* collisionManager;
	void BeforeDraw();
	void AfterDraw();
public:
	BaseGame();
	~BaseGame();
	int Init();
	virtual void Initialize() = 0;
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DeInitialize() = 0;
	void DrawShape(Triangle* triangle);
	Triangle* CreateTriangle();
};

#endif