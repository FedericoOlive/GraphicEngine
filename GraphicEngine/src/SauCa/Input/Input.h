#ifndef INPUT_H
#define INPUT_H
#include <glm/glm/vec2.hpp>

#include "Exports.h"
#include "KeyCodes.h"
#include "Window.h"
#include "Utility/Event.h"
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class SAUCA_API Input
{
private:
	Window* window;

public:
	static Event<double, double> OnMouseMove;
	static Event<double, double> OnMouseScrollMove;
	
	static int key;
	static int action;
	static glm::vec2 mousePos;

	Input();
	~Input();

	void InitInput(Window* _window);
	static bool IsKeyReleased(KeyCode keyCode);
	static bool IsKeyDown(KeyCode keyCode);
	static bool IsKeyPressed(KeyCode keyCode);
	int GetKey();
};

#endif