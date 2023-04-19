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
    material->shader->Use();
    int shaderID = material->shader->ID;
    if (material->hasTexture)
    {
        unsigned int locationTexture = glGetUniformLocation(shaderID, "ourTexture");
        glUniform1f(locationTexture, (GLfloat)textureID);
    }
    
    unsigned int locationColor = glGetUniformLocation(shaderID, "colorTint");
    unsigned int locationAlpha = glGetUniformLocation(shaderID, "alpha");
    unsigned int transformLoc = glGetUniformLocation(shaderID, "modelMatrix");
    unsigned int viewLoc = glGetUniformLocation(shaderID, "viewMatrix");
    unsigned int projectionLoc = glGetUniformLocation(shaderID, "projectionMatrix");
    
    glUniform3fv(locationColor, 1, value_ptr(material->colorTint));
    glUniform1fv(locationAlpha, 1, &alpha);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    
	// Todo: Agregar layers para distintas cámaras
    glm::mat4 viewMatrix = cameras.front()->viewMatrix;
    glm::mat4 projectionMatrix = cameras.front()->projectionMatrix;
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    
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