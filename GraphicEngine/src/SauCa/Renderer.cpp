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

}

void Renderer::CreateShader()
{
    shaderSolid = new Shader(false);
    shaderTexture = new Shader(true);

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
    glm::mat4 viewMatrix = cameras.front()->viewMatrix;
    glm::mat4 projectionMatrix = cameras.front()->projectionMatrix;
	
    material->shader->setMat4("projectionMatrix", projectionMatrix);
    material->shader->setMat4("viewMatrix", viewMatrix);
    material->shader->setMat4("modelMatrix", model);
    material->shader->setVec3("colorTint", material->colorTint);
    material->shader->setFloat("alpha", alpha);
	
    //if (material->hasTexture && textureID != NULL)
    {
        unsigned int locationTexture = glGetUniformLocation(shaderID, "ourTexture");
        glUniform1f(locationTexture, (GLfloat)textureID);
        
        //// Basic
        material->shader->setVec3("lightPos", { 0, 0, 0 });
        material->shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        // Both
        material->shader->setVec3("viewPos", cameras.front()->transform->GetWorldPosition());

        // Multiple
        material->shader->setInt("material.diffuse", 0);
        material->shader->setInt("material.specular", 0);
        material->shader->setFloat("material.shininess", 32);
        material->shader->setVec3("material.colorTint", material->colorTint);
        material->shader->setBool("material.hasTexture", material->hasTexture);

        // Set lights
        material->shader->setInt("dirLightAmount", directionalLights.size());
        material->shader->setInt("pointLightAmount", pointLights.size());
        material->shader->setInt("spotLightAmount", spotLights.size());

        int i = 0;
        for (auto dirLight = directionalLights.begin(); dirLight != directionalLights.end(); ++dirLight)
        {
            if ((*dirLight)->isEnable && (*dirLight)->gameobject->isActive)
            {
                string dirLightString = "dirLights[" + to_string(i) + "].";

                material->shader->setVec3(dirLightString + "direction", (*dirLight)->transform->forward());
                material->shader->setVec3(dirLightString + "ambient", (*dirLight)->ambient);
                material->shader->setVec3(dirLightString + "diffuse", (*dirLight)->diffuse);
                material->shader->setVec3(dirLightString + "specular", (*dirLight)->specular);

                i++;
                if (i > 4)
                    break;
            }
        }

        i = 0;
        for (auto pointLight = pointLights.begin(); pointLight != pointLights.end(); ++pointLight)
        {
            if ((*pointLight)->isEnable && (*pointLight)->gameobject->isActive)
            {
                string pointLightString = "pointLights[" + to_string(i) + "].";

                material->shader->setVec3(pointLightString + "position", (*pointLight)->transform->GetWorldPosition());
                material->shader->setVec3(pointLightString + "ambient", (*pointLight)->ambient);
                material->shader->setVec3(pointLightString + "diffuse", (*pointLight)->diffuse);
                material->shader->setVec3(pointLightString + "specular", (*pointLight)->specular);
                material->shader->setFloat(pointLightString + "constant", (*pointLight)->constant);
                material->shader->setFloat(pointLightString + "linear", (*pointLight)->linear);
                material->shader->setFloat(pointLightString + "quadratic", (*pointLight)->quadratic);

                i++;
                if (i > 4)
                    break;
            }
        }

        i = 0;
        for (auto spotLight = spotLights.begin(); spotLight != spotLights.end(); ++spotLight)
        {
            if ((*spotLight)->isEnable && (*spotLight)->gameobject->isActive)
            {
                string spotLightString = "spotLights[" + to_string(i) + "].";

                material->shader->setVec3(spotLightString + "position", (*spotLight)->transform->GetWorldPosition());
                material->shader->setVec3(spotLightString + "direction", cameras.front()->transform->forward());
                material->shader->setVec3(spotLightString + "ambient", (*spotLight)->ambient);
                material->shader->setVec3(spotLightString + "diffuse", (*spotLight)->diffuse);
                material->shader->setVec3(spotLightString + "specular", (*spotLight)->specular);
                material->shader->setFloat(spotLightString + "constant", (*spotLight)->constant);
                material->shader->setFloat(spotLightString + "linear", (*spotLight)->linear);
                material->shader->setFloat(spotLightString + "quadratic", (*spotLight)->quadratic);
                material->shader->setFloat(spotLightString + "cutOff", glm::cos(glm::radians((*spotLight)->cutOff)));
                material->shader->setFloat(spotLightString + "outerCutOff", glm::cos(glm::radians((*spotLight)->outerCutOff)));

                i++;
                if (i > 4)
                    break;
            }
        }
    }
        
    //// bind diffuse map
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, diffuseMap);
    //// bind specular map
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, specularMap);
	
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
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