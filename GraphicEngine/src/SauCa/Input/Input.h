#ifndef INPUT_H
#define INPUT_H

#include "Exports.h"
#include "KeyCodes.h"
#include "Window.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class SAUCA_API Input
{
private:
	Window* window;

public:
	Input();
	~Input();

	void InitInput(Window* _window);
	bool IsKeyReleased(KeyCode keyCode);
	bool IsKeyDown(KeyCode keyCode);
	bool IsKeyPressed(KeyCode keyCode);
	int GetKey();	
	int static key;
	int static action;
};

#endif