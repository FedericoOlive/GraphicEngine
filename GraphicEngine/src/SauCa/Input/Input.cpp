#include "Input.h"

int Input::key = 0;
int Input::action = 0;

Input::Input()
{
	
}

Input::~Input()
{
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::key = key;
	Input::action = action;
}

void Input::InitInput(Window* _window)
{
	window = _window;
	glfwSetKeyCallback(window->GetWindow(), keyCallback);
	/*glfwSetInputMode(window->GetWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);*/
}

bool Input::IsKeyReleased(KeyCode keyCode)
{
	bool isHappening = ((int)keyCode == key && action == (int)KeyState::KEY_RELEASE);
	if (isHappening) {
		action = 3;
	}
	return isHappening;
}

bool Input::IsKeyPressed(KeyCode keyCode)
{
	bool isHappening = ((int)keyCode == key && action == (int)KeyState::KEY_PRESS);
	if (isHappening) {
		action = 3;
	}
	return isHappening;
}

bool Input::IsKeyDown(KeyCode keyCode)
{
	bool isHappening = ((int)keyCode == key && (action == (int)KeyState::KEY_HOLD || action == (int)KeyState::KEY_PRESS));
	return isHappening;
}

int Input::GetKey()
{
	return key;
}

