#ifndef RENDERER_H
#define RENDERER_H
#include <list>

#include "glew.h"
#include "Window.h"
#include "Entity/Entity2D/Material.h"
#include "GameObjects/Component.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
class Camera;

static class SAUCA_API Renderer
{
private:
	Material* defaultMaterialSolid;
	Material* defaultMaterialTexture;
	
	static std::list<Component*> renderList;
	static std::list<Camera*> cameras;
public:
	static void AddToRenderList(Component* component);
	
	Renderer();
	~Renderer();
	void CreateRenderer();
	void Clear(GLbitfield field);
	void Draw();
	void SwapBuffers(GLFWwindow* window);
	void CreateShader();
	void DrawShape(int sizeIndices, unsigned int& VAO, Material* material, float alpha, glm::mat4 model);
	void DrawSprite(unsigned int textureID, int sizeIndices, unsigned int& VAO, Material* material, float alpha, glm::mat4 model);
	void DrawEntity2D(unsigned int textureID, int sizeIndices, unsigned int& VAO, Material* material, float alpha, glm::mat4 model);
	void BindVertex(float* vertices, int sizeVertices, int* indices, int sizeIndices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void BindVertexs(float* vertices, int sizeVertices, int* indices, int sizeIndices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void SetShapeAttributes();
	void SetSpriteAttributes();
	Material* GetMaterialTexture() { return defaultMaterialTexture; }
	Material* GetMaterialSolid() { return defaultMaterialSolid; }
	void BindTextures(unsigned int& texture);

	static void RemoveCamera(Camera* cam);
	static void AddCamera(Camera* cam);
	
};

#endif