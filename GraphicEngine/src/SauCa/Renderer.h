#ifndef RENDERER_H
#define RENDERER_H

#include "Shaders/Shader.h"
#include "Window.h"

class SAUCA_API Renderer
{
private:
	
	unsigned int VBO;
	unsigned int VAO;
	Shader* shader;

public:
	Renderer();
	~Renderer();
	void Clear(GLbitfield field);
	void SwapBuffers(GLFWwindow* window);
	void CreateShader();
	void DrawTriangle();
	void DestroyShader();
	void Draw();
	void BindVertex(float* vertices, int size);
};

#endif