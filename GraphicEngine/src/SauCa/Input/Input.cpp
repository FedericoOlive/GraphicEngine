#include "Input.h"

int Input::key = 0;
int Input::action = 0;
glm::vec2 Input::mousePos = { 0.0, 0.0 };
Event<double, double> Input::OnMouseMove;
Event<double, double> Input::OnMouseScrollMove;

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	// Acceder a los miembros de la instancia Input utilizando el puntero input
	glm::vec2 currentPos = { xposIn, yposIn };
	glm::vec2 lastPos = Input::mousePos;
	glm::vec2 offset = currentPos - lastPos;

	Input::mousePos = currentPos;
	Input::OnMouseMove.Invoke(offset.x, offset.y);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::OnMouseScrollMove.Invoke(xoffset, yoffset);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::key = key;
	Input::action = action;
}

Input::Input()
{
	mousePos = { 0.0, 0.0 };
}
Input::~Input(){}

void Input::InitInput(Window* _window)
{
	window = _window;
	glfwSetKeyCallback(window->GetWindow(), keyCallback);
	glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);
	glfwSetScrollCallback(window->GetWindow(), ScrollCallback);
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