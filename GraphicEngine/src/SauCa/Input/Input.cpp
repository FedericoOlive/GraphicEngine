#include "Input.h"

int Input::key = 0;

Input::Input()
{
	
}

Input::~Input()
{
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::key = key;
}

void Input::InitInput(Window* _window)
{
	window = _window;
	glfwSetKeyCallback(window->GetWindow(), keyCallback);
}

bool Input::IsKey(KeyState keyState, KeyCode keyCode)
{
	int lastKeyStatus = glfwGetKey(window->GetWindow(), (int)keyCode);
	return lastKeyStatus == (int)keyState;
}

int Input::GetKey()
{
	return key;
}

