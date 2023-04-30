#ifndef INPUT_H
#define INPUT_H
#include <list>
#include <glm/glm/vec2.hpp>

#include "Exports.h"
#include "KeyCodes.h"
#include "Window.h"
#include "Utility/Event.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class SAUCA_API Input
{
public:
	static Event<double, double> OnMouseMove;
	static Event<double, double> OnMouseScrollMove;
	
	static std::list<KeyCode> currentKeysDown;
	static glm::vec2 mousePos;

	Input();
	~Input();

	void InitInput(Window* window);
	static bool IsKeyUp(KeyCode keyCode);
	static bool IsKeyDown(KeyCode keyCode);
	static bool IsKeyHolding(KeyCode keyCode);
};

#endif