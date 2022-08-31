#ifndef RENDERER_H
#define RENDERER_H

#include "Exports.h"
#include "Window.h"

class SAUCA_API Renderer
{
private:
	unsigned int VBO;
	unsigned int VAO;
public:
	Renderer();
	~Renderer();
	void Clear(GLbitfield field);
	void SwapBuffers(GLFWwindow* window);
	void CreateShader();
	void DrawTriangle();
	void DestroyShader();
};

#endif