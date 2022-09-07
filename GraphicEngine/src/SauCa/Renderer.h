#ifndef RENDERER_H
#define RENDERER_H

#include "Exports.h"
#include "Window.h"
#include "Shaders/Shader.h"

class SAUCA_API Renderer
{
private:
	std::string vspath;
	std::string fspath;
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
};

#endif