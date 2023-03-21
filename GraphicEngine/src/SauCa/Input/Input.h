#ifndef INPUT_H
#define INPUT_H

#include "Exports.h"
#include "KeyCodes.h"
#include "Window.h"
#include "Utility/Event.h"
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class SAUCA_API Input
{
private:
	Window* window;

public:
	static Event<double, double> OnMouseMove;
	static Event<double, double> OnMouseScrollMove;
	
	int static key;
	int static action;
	
	Input();
	~Input();
	
	void MouseCallback(GLFWwindow* window, double xposIn, double yposIn, Input* input);
	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset, Input* input);
		
	void InitInput(Window* _window);
	bool IsKeyReleased(KeyCode keyCode);
	bool IsKeyDown(KeyCode keyCode);
	bool IsKeyPressed(KeyCode keyCode);
	int GetKey();
};

#endif