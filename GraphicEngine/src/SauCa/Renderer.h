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
	Shader* shader;
	Shader* shaderTexture;

public:
	Renderer();
	~Renderer();
	void Clear(GLbitfield field);
	void SwapBuffers(GLFWwindow* window);
	void CreateShader();
	void DrawShape(int sizeIndices, unsigned int& VAO);
	void DrawSprite(unsigned int textureID, int sizeIndices, unsigned int& VAO);
	void BindVertex(float* vertices, int sizeVertices, int* indices, int sizeIndices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void SetShapeAttributes();
	void SetSpriteAttributes();
};

#endif