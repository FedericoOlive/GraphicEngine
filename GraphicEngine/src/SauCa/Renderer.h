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

class SAUCA_API Renderer
{
private:
	static Shader* defaultShaderSkybox;
	static Shader* defaultShaderSolid;
	static Shader* defaultShaderTexture;
	static Shader* defaultShader;
	static Shader* defaultShaderAnim;
	
	static std::list<Component*> allRenderList;
	
public:
	//static std::list<Animator*> allAnimatorList;
	static std::list<Camera*> cameras;
	std::list<DirectionalLight*> directionalLights;
	std::list<PointLight*> pointLights;
	std::list<SpotLight*> spotLights;
	
	static void AddToRenderList(Component* component);
	
	Renderer();
	~Renderer();
	void CreateRenderer();
	void Clear(GLbitfield field);
	void Draw(double deltaTime);
	void SwapBuffers(GLFWwindow* window);
	void CreateShader();
	
	void DrawEntity(unsigned int VAO, int sizeIndex, glm::mat4 model, unsigned int textureID, Material* material, float alpha, Camera* camera);
	void DrawModel(glm::mat4 model, unsigned textureID, Material* material, float alpha, Camera* camera, std::vector<Mesh> meshes, std::vector<glm::mat4>* transforms);
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

	static Shader* GetDefaultShaderSkybox() { return defaultShaderSkybox; }
	static Shader* GetDefaultShaderSolid() { return defaultShaderSolid; }
	static Shader* GetDefaultShaderTexture() { return defaultShaderTexture; }
	static Shader* GetDefaultShader() { return defaultShader; }
	static Shader* GetDefaultShaderAnim() { return defaultShaderAnim; }
	void BindTextures(unsigned int& texture);

	static void RemoveCamera(Camera* cam);
	static void AddCamera(Camera* cam);

	static void DrawLine(const glm::vec3& startPoint, const glm::vec3& endPoint, float lineWidth = 2.0f, glm::vec3 color = { 1, 0, 0 }, Camera* camera = nullptr);
};

#endif