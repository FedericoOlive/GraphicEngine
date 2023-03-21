#include "Input.h"

int Input::key = 0;
int Input::action = 0;
Event<double, double> Input::OnMouseMove;
Event<double, double> Input::OnMouseScrollMove;

Input::Input(){}
Input::~Input(){}

void Input::MouseCallback(GLFWwindow* window, double xposIn, double yposIn, Input* input)
{
	// Acceder a los miembros de la instancia Input utilizando el puntero input
	input->OnMouseMove.Invoke(xposIn, yposIn);
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset, Input* input)
{
	// Acceder a los miembros de la instancia Input utilizando el puntero input
	input->OnMouseScrollMove.Invoke(xoffset, yoffset);
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

	glfwSetCursorPosCallback(window->GetWindow(), [](GLFWwindow* window, double xposIn, double yposIn)
		{
			Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
			input->MouseCallback(window, xposIn, yposIn, input);
		});

	glfwSetScrollCallback(window->GetWindow(), [](GLFWwindow* window, double xoffset, double yoffset)
		{
			Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
			input->ScrollCallback(window, xoffset, yoffset, input);
		});
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