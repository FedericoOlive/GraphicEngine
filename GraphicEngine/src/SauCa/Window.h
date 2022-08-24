#ifndef WINDOW_H
#define WINDOW_H

#include "Exports.h"
#include "glew.h"
#include <glfw3.h>

class SAUCA_API Window
{
	private:
		GLFWwindow* window;
	public:
		Window();
		~Window();
		int InitLibrary();
		void CreateWindow();
		int CheckWindow(GLFWwindow* window);
		void AssignContext(GLFWwindow* window);
		bool WindowShouldClose(GLFWwindow* window);
		void TerminateLibrary();
		void PollEvents();
		GLFWwindow* GetWindow();

};

#endif