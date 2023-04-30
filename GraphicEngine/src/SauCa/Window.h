#ifndef WINDOW_H
#define WINDOW_H

#include "Exports.h"
#include <glfw3.h>
#include <string>

class SAUCA_API Window
{
private:
	std::string windowBaseName;
public:
	static GLFWwindow* window;

	static float Screen_Width;
	static float Screen_Height;

	Window();
	~Window();
	int InitLibrary();
	void CreateWindow();
	void SetWindowTitle(std::string newTitle);
	void AddStringToNameWindow(std::string stringToAdd) const;
	int CheckWindow(GLFWwindow* window);
	void AssignContext(GLFWwindow* window);
	bool WindowShouldClose(GLFWwindow* window);
	void TerminateLibrary();
	void PollEvents();
	GLFWwindow* GetWindow();
	void LockCursor(bool enable);
};

#endif