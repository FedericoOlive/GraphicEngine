#include "Renderer.h"
#include "GameObjects/GameObject.h"
#include "Render/Camera.h"

using namespace std;

std::list<Component*> Renderer::renderList;
std::list<Camera*> Renderer::cameras;

void Renderer::AddToRenderList(Component* component)
{
    renderList.push_back(component);
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
    delete defaultMaterialSolid;
    delete defaultMaterialTexture;
}

void Renderer::CreateShader()
{
    defaultMaterialSolid = new Material(new Shader(false), false);
    defaultMaterialTexture = new Material(new Shader(true), true);
    defaultMaterialLight = new Material(new Shader(true), true);
    std::cout << "\n";
}

void Renderer::CreateRenderer()
{
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DrawEntity(unsigned int VAO, int sizeIndex, glm::mat4 model, unsigned int textureID, Material* material, float alpha)
{
    // Todo: Agregar layers para distintas cámaras

	material->shader->Use();
    int shaderID = material->shader->ID;
	
    if (material->hasTexture)
    {
        unsigned int locationTexture = glGetUniformLocation(shaderID, "ourTexture");
        glUniform1f(locationTexture, (GLfloat)textureID);
    }

    glm::mat4 viewMatrix = cameras.front()->viewMatrix;
    glm::mat4 projectionMatrix = cameras.front()->projectionMatrix;

    material->shader->setVec3("colorTint", material->colorTint);
    material->shader->setFloat("alpha", alpha);
    material->shader->setMat4("modelMatrix", model);
    material->shader->setMat4("viewMatrix", viewMatrix);
    material->shader->setMat4("projectionMatrix", projectionMatrix);
    material->shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    material->shader->setVec3("lightPos", { 0, 0, 0});
    material->shader->setVec3("viewPos", cameras.front()->transform->GetWorldPosition());
	
    material->shader->setFloat("material.shininess", 320);
	
    material->shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    material->shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    material->shader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    material->shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    material->shader->setVec3("pointLights[0].position", { 5, 5, 5 });
    material->shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    material->shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    material->shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    material->shader->setFloat("pointLights[0].constant", 1.0f);
    material->shader->setFloat("pointLights[0].linear", 0.09f);
    material->shader->setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    material->shader->setVec3("pointLights[1].position", { 5, 5, -5 });
    material->shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    material->shader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    material->shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    material->shader->setFloat("pointLights[1].constant", 1.0f);
    material->shader->setFloat("pointLights[1].linear", 0.09f);
    material->shader->setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    material->shader->setVec3("pointLights[2].position", { -5, 5, 5 });
    material->shader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    material->shader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    material->shader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    material->shader->setFloat("pointLights[2].constant", 1.0f);
    material->shader->setFloat("pointLights[2].linear", 0.09f);
    material->shader->setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    material->shader->setVec3("pointLights[3].position", { -5, 5, -5 });
    material->shader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    material->shader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    material->shader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    material->shader->setFloat("pointLights[3].constant", 1.0f);
    material->shader->setFloat("pointLights[3].linear", 0.09f);
    material->shader->setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight
    material->shader->setVec3("spotLight.position", cameras.front()->transform->GetWorldPosition());
    material->shader->setVec3("spotLight.direction", cameras.front()->transform->forward());
    material->shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    material->shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    material->shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    material->shader->setFloat("spotLight.constant", 1.0f);
    material->shader->setFloat("spotLight.linear", 0.09f);
    material->shader->setFloat("spotLight.quadratic", 0.032f);
    material->shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    material->shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
    
    // bind diffuse map
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, diffuseMap);
    //// bind specular map
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, specularMap);
	
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear(GLbitfield field)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw()
{
    for (auto iter = renderList.begin(); iter != renderList.end(); ++iter)
    {
        bool isEnable = (*iter)->isEnable;
        bool isActive = (*iter)->gameobject->isActive;  // Todo: Faltaría ActiveInHierarchy.

        if (isEnable && isActive)
            (*iter)->Draw();
    }
}

void Renderer::SwapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Renderer::BindGenBufferObject(unsigned int& buffer)
{
    glGenVertexArrays(1, &buffer);
    glBindVertexArray(buffer);
}

void Renderer::UnBindGenBufferObject()
{
    glBindVertexArray(0);
}

void Renderer::GenBuffer(int amount, unsigned int& buffer)
{
    // Generar objeto de búfer de vértices para posición de vértices
    glGenBuffers(amount, &buffer);
}

void Renderer::BindBufferData(unsigned int buffer, int atribPointer, int atribPointerSize, int size, float* arrayData, int modeDataStore)
{
	// Enlazar objeto de búfer de vértices para posición de vértices
    glEnableVertexAttribArray(atribPointer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), arrayData, (modeDataStore == 0) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    glVertexAttribPointer(atribPointer, atribPointerSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Renderer::BindIndex(unsigned int buffer, int size, int* arrayData)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), arrayData, GL_STATIC_DRAW);
}

void Renderer::UnBindObject(unsigned int& VAO, unsigned int& VBO, unsigned int& COL, unsigned int& LVAO, unsigned int& UVB, unsigned int& EBO)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &COL);
    glDeleteBuffers(1, &LVAO);
    glDeleteBuffers(1, &UVB);
    glDeleteBuffers(1, &EBO);
}

void Renderer::BindTextures(unsigned int& texture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Renderer::RemoveCamera(Camera* cam)
{
    for (auto iter = cameras.begin(); iter != cameras.end(); ++iter)
    {
        if ((*iter) == cam)
        {
            cameras.erase(iter);
            break;
        }
    }
}

void Renderer::AddCamera(Camera* cam)
{
    cameras.push_back(cam);
}