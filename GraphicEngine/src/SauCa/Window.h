#pragma once
#include "Exports.h"

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

