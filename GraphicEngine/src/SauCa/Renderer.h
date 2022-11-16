#ifndef RENDERER_H
#define RENDERER_H

#include "glew.h"
#include "Window.h"
#include "Entity/Entity2D/Material.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

class SAUCA_API Renderer
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Material* defaultMaterialSolid;
	Material* defaultMaterialTexture;
public:
	Renderer();
	~Renderer();
	void Clear(GLbitfield field);
	void SwapBuffers(GLFWwindow* window);
	void CreateShader();
	void DrawShape(int sizeIndices, unsigned int& VAO, Material* material, float alpha, glm::mat4 model);
	void DrawSprite(unsigned int textureID, int sizeIndices, unsigned int& VAO, Material* material, float alpha, glm::mat4 model);
	void DrawEntity2D(unsigned int textureID, int sizeIndices, unsigned int& VAO, Material* material, float alpha, glm::mat4 model);
	void BindVertex(float* vertices, int sizeVertices, int* indices, int sizeIndices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void SetShapeAttributes();
	void SetSpriteAttributes();

	Material* GetMaterialTexture() { return defaultMaterialTexture; }
	Material* GetMaterialSolid() { return defaultMaterialSolid; }
};

#endif