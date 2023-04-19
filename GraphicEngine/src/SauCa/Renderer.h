#ifndef RENDERER_H
#define RENDERER_H
#include <list>

#include "glew.h"
#include "Window.h"
#include "Entity/Entity2D/Material.h"
#include "GameObjects/Component.h"
#include "glm/glm/glm.hpp"
#include "Entity/VertexData.h"

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
	
	void DrawEntity(unsigned int VAO, int sizeIndex, glm::mat4 model, unsigned int textureID, Material* material, float alpha);

	void BindGenBufferObject(unsigned int& buffer);
	void UnBindGenBufferObject();
	void GenBuffer(int amount, unsigned int& buffer);	
	void BindBufferData(unsigned int buffer, int atribPointer, int atribPointerSize, int size, float* arrayData, int modeDataStore);
	void BindIndex(unsigned int buffer, int size, int* arrayData);
		
	void UnBindObject(unsigned int& VAO, unsigned int& VBO, unsigned int& COL, unsigned int& LVAO, unsigned int& UVB, unsigned int& EBO);
	Material* GetMaterialTexture() { return defaultMaterialTexture; }
	Material* GetMaterialSolid() { return defaultMaterialSolid; }
	void BindTextures(unsigned int& texture);

	static void RemoveCamera(Camera* cam);
	static void AddCamera(Camera* cam);	
};

#endif