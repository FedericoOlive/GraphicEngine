#include "Input.h"

#include <iostream>
glm::vec2 Input::mousePos = { 0.0, 0.0 };
Event<double, double> Input::OnMouseMove;
Event<double, double> Input::OnMouseScrollMove;
std::list<KeyState> Input::currentKeysDown;

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
		for (auto iter = Input::currentKeysDown.begin(); iter != Input::currentKeysDown.end(); ++iter)
		{
			if ((*iter).keyCode == (KeyCode)key)
			{
				Input::currentKeysDown.erase(iter);
				break;
			}
		}
		break;
		
	case GLFW_PRESS:
		Input::currentKeysDown.push_back({ (KeyCode)key, false });
		//std::cout << "Key Down: " << (int)key << " State: " << false << "\n";
		break;
		
	case GLFW_REPEAT:
		for (auto iter = Input::currentKeysDown.begin(); iter != Input::currentKeysDown.end(); ++iter)
		{
			if ((*iter).keyCode == (KeyCode)key && !((*iter).isHolding))
				(*iter).isHolding = true;
			
			//std::cout << "Key Hold: " << (int)((*iter).keyCode) << " State: " << (*iter).isHolding << "\n";
		}
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

bool Input::IsKeyUp(KeyCode keycode)
{
	int aux = glfwGetKey(Window::window, (int)keycode);
	return aux == GLFW_RELEASE;
}

bool Input::IsKeyDown(KeyCode keycode)
{
	if (!currentKeysDown.empty())
		for (auto iter = currentKeysDown.begin(); iter != currentKeysDown.end(); ++iter)
			if ((*iter).keyCode == keycode)
				return !(*iter).isHolding;
	
	return false;
}

bool Input::IsKeyHolding(KeyCode keycode)
{
	if (!currentKeysDown.empty())
		for (auto iter = currentKeysDown.begin(); iter != currentKeysDown.end(); ++iter)
			if ((*iter).keyCode == keycode)
				return true;

	return false;
}

KeyState Input::GetKey()
{
	return currentKeysDown.back();
}