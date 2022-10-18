#include "Input.h"

Input::Input()
{
	
}

Input::~Input()
{
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}
}

void Input::InitInput(Window* _window)
{
	window = _window;
}

bool Input::IsKey(KeyState keyState, KeyCode keyCode)
{
	int lastKeyStatus = glfwGetKey(window->GetWindow(), (int)keyCode);
	return lastKeyStatus == (int)keyState;
}

int Input::GetKey()
{
	return 0;
}