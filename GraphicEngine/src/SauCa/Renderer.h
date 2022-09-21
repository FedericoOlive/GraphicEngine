#ifndef RENDERER_H
#define RENDERER_H

#include "Shaders/Shader.h"
#include "Window.h"
#include "../../../libs/glm/glm/glm.hpp"
#include "../../../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../../../libs/glm/glm/gtc/type_ptr.hpp"

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