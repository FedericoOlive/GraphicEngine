#ifndef INPUT_H
#define INPUT_H
#include <list>
#include <glm/vec2.hpp>

#include "Exports.h"
#include "KeyCodes.h"
#include "Window.h"
#include "Utility/Event.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Input
{
public:
	static std::list<KeyCode> currentKeysDown;
	static std::list<MouseCode> currentMouseButtonsDown;
	static glm::vec2 mousePos;

	Input();
	~Input();
	void InitInput(Window* window);
	
	
	SAUCA_API static Event<double, double> OnMouseMove;
	SAUCA_API static Event<double, double> OnMouseScrollMove;
	
	SAUCA_API static bool IsKeyUp(KeyCode keyCode);
	SAUCA_API static bool IsKeyDown(KeyCode keyCode);
	SAUCA_API static bool IsKeyHolding(KeyCode keyCode);
	
	SAUCA_API static bool IsMouseButtonUp(MouseCode mouseCode);
	SAUCA_API static bool IsMouseButtonDown(MouseCode mouseCode);
	SAUCA_API static bool IsMouseButtonHolding(MouseCode mouseCode);
};

#endif