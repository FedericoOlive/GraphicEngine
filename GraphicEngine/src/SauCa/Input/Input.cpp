#include "Input.h"
#include <iostream>

Event<double, double> Input::OnMouseMove;
Event<double, double> Input::OnMouseScrollMove;
std::list<KeyCode> Input::currentKeysDown;
std::list<MouseCode> Input::currentMouseButtonsDown;
glm::vec2 Input::mousePos = { 0.0, 0.0 };

void MouseMoveCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	glm::vec2 currentPos = { xposIn, yposIn };
	glm::vec2 lastPos = Input::mousePos;
	glm::vec2 offset = currentPos - lastPos;

	Input::mousePos = currentPos;
	Input::OnMouseMove.Invoke(offset.x, offset.y);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_RELEASE:
		Input::currentMouseButtonsDown.remove((MouseCode)button);
		break;

	case GLFW_PRESS:
		Input::currentMouseButtonsDown.push_back((MouseCode)button);
		break;

	case GLFW_REPEAT:
		Input::currentMouseButtonsDown.remove((MouseCode)button);
		break;

	default:
		break;
	}
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::OnMouseScrollMove.Invoke(xoffset, yoffset);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_RELEASE:
		Input::currentKeysDown.remove((KeyCode)key);
		break;
		
	case GLFW_PRESS:
		Input::currentKeysDown.push_back((KeyCode)key);
		break;
		
	case GLFW_REPEAT:
		Input::currentKeysDown.remove((KeyCode)key);
		break;
		
	default:
		break;
	}
}

Input::Input()
{
	mousePos = { 0.0, 0.0 };
}

Input::~Input(){}

void Input::InitInput(Window* window)
{
	glfwSetKeyCallback(window->GetWindow(), keyCallback);
	glfwSetMouseButtonCallback(window->GetWindow(), MouseButtonCallback);
	glfwSetCursorPosCallback(window->GetWindow(), MouseMoveCallback);
	glfwSetScrollCallback(window->GetWindow(), ScrollCallback);
}

bool Input::IsKeyUp(KeyCode keyCode)
{
	int state = glfwGetKey(Window::window, (int)keyCode);
	return state == GLFW_RELEASE;
}

bool Input::IsKeyDown(KeyCode keyCode)
{
	int state = glfwGetKey(Window::window, (int)keyCode);
	if (state == GLFW_PRESS)
	{
		return std::find(currentKeysDown.begin(), currentKeysDown.end(), keyCode) != currentKeysDown.end();
	}

	return false;
}

bool Input::IsKeyHolding(KeyCode keyCode)
{
	int state = glfwGetKey(Window::window, (int)keyCode);
	return state == GLFW_PRESS;
}

bool Input::IsMouseButtonUp(MouseCode mouseCode)
{
	int state = glfwGetMouseButton(Window::window, (int)mouseCode);
	return state == GLFW_RELEASE;
}

bool Input::IsMouseButtonDown(MouseCode mouseCode)
{
	int state = glfwGetMouseButton(Window::window, (int)mouseCode);
	if (state == GLFW_PRESS)
	{
		return std::find(currentMouseButtonsDown.begin(), currentMouseButtonsDown.end(), mouseCode) != currentMouseButtonsDown.end();
	}

	return false;
}

bool Input::IsMouseButtonHolding(MouseCode mouseCode)
{
	int state = glfwGetMouseButton(Window::window, (int)mouseCode);
	return state == GLFW_PRESS;
}