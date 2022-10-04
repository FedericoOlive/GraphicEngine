#ifndef RENDERER_H
#define RENDERER_H

#include "Shaders/Shader.h"
#include "glew.h"
#include "Window.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

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
	void DrawShape(int sizeIndices, unsigned int& VAO, glm::mat4 transform);
	void DrawSprite(unsigned int textureID, int sizeIndices, unsigned int& VAO, glm::vec4 color, glm::mat4 transform);
	void BindVertex(float* vertices, int sizeVertices, int* indices, int sizeIndices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void SetShapeAttributes();
	void SetSpriteAttributes();
};

#endif