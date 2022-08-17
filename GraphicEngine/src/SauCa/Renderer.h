#ifndef RENDERER_H
#define RENDERER_H

#include "Exports.h"
#include "Window.h"

class SAUCA_API Renderer
{
	private:
	public:
		Renderer();
		~Renderer();
		void Clear(GLbitfield field);
		void SwapBuffers(GLFWwindow* window);
};

#endif