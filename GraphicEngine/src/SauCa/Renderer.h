#ifndef RENDERER_H
#define RENDERER_H
#include <list>

#include "glew/glew.h"
#include "Window.h"
#include "Entity/Entity2D/Material.h"
#include "GameObjects/Component.h"
#include "glm/glm.hpp"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"
#include "Entity/Entity3D/Mesh.h"
#include "Entity/VertexData.h"

class Camera;

static class SAUCA_API Renderer
{
private:
	Shader* defaultShaderSkybox;
	Shader* defaultShaderSolid;
	Shader* defaultShaderTexture;
	Shader* defaultShader;
	
	static std::list<Component*> allRenderList;
	
public:
	static std::list<Camera*> cameras;
	std::list<DirectionalLight*> directionalLights;
	std::list<PointLight*> pointLights;
	std::list<SpotLight*> spotLights;
	
	static void AddToRenderList(Component* component);
	
	Renderer();
	~Renderer();
	void CreateRenderer();
	void Clear(GLbitfield field);
	void Draw();
	void SwapBuffers(GLFWwindow* window);
	void CreateShader();
	
	void DrawEntity(unsigned int VAO, int sizeIndex, glm::mat4 model, unsigned int textureID, Material* material, float alpha, Camera* camera);
	void DrawModel(glm::mat4 model, unsigned textureID, Material* material, float alpha, Camera* camera, std::vector<Mesh> meshes);
	void DrawCubemap(unsigned int VAO, unsigned int cubemapTexture, Material* material, std::list<Camera*> cameras);
	static void SetMatrix(Shader* shader, Camera* camera, glm::mat4 model);
	void SetMaterial(Material* material, float alpha, unsigned int textureID);
	void SetLights(Material* material);
	
	void BindGenBufferObject(unsigned int& buffer);
	void UnBindGenBufferObject();
	void GenBuffer(int amount, unsigned int& buffer);
	void BindBufferData(unsigned int buffer, int atribPointer, int atribPointerSize, int size, float* arrayData, int modeDataStore);
	void BindIndex(unsigned int buffer, int size, int* arrayData);
	void UnBindObject(VertexData* vertexData);
	void UnBindObject(unsigned int& VAO, unsigned int& VBO, unsigned int& CBO, unsigned int& NBO, unsigned int& UVB, unsigned int& EBO);

	Shader* GetDefaultShaderSkybox() const { return defaultShaderSkybox; }
	Shader* GetDefaultShaderSolid() const { return defaultShaderSolid; }
	Shader* GetDefaultShaderTexture() const { return defaultShaderTexture; }
	Shader* GetDefaultShader() const { return defaultShader; }
	void BindTextures(unsigned int& texture);

	static void RemoveCamera(Camera* cam);
	static void AddCamera(Camera* cam);

	void DrawLine(const glm::vec3& startPoint, const glm::vec3& endPoint, float lineWidth = 2, glm::vec3 color = { 1, 0, 0 }, Camera* camera);
};

#endif