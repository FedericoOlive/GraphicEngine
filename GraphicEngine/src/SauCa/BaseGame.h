#ifndef BASEGAME_H
#define BASEGAME_H

#include "Exports.h"
#include <iostream>
#include "Input.h"
#include "CollisionManager.h"
#include "Renderer.h"
#include "Window.h"
using namespace std;

class SAUCA_API BaseGame
{
private:
	Input* input;
	Window* window;
	Renderer* renderer;
	CollisionManager* collisionManager;
public:
	int Init();
	
};

#endif