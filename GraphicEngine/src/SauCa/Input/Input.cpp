#include "Input.h"
#include <iostream>

glm::vec2 Input::mousePos = { 0.0, 0.0 };
Event<double, double> Input::OnMouseMove;
Event<double, double> Input::OnMouseScrollMove;
std::list<KeyCode> Input::currentKeysDown;

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
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
	switch (action)
	{
	case GLFW_RELEASE:
		Input::currentKeysDown.remove((KeyCode)key);
		//std::cout << "Key Down: " << key << " State: RELEASE \n";
		break;
		
	case GLFW_PRESS:
		Input::currentKeysDown.push_back((KeyCode)key);
		//std::cout << "Key Down: " << key << " State: PRESS \n";
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
	glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);
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
		if (std::find(currentKeysDown.begin(), currentKeysDown.end(), keyCode) != currentKeysDown.end())
		{
			currentKeysDown.remove(keyCode);
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool Input::IsKeyHolding(KeyCode keyCode)
{
	int state = glfwGetKey(Window::window, (int)keyCode);
	return state == GLFW_PRESS;
}