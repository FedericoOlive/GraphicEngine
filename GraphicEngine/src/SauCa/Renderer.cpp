#include "Renderer.h"

using namespace std;

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
    viewMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::mat4(1.0f);
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    defaultMaterialSolid = new Material(new Shader(false), false);
    defaultMaterialTexture = new Material(new Shader(true), true);
}

void Renderer::DrawEntity2D(unsigned int textureID, int sizeIndices, unsigned int& VAO, Material* material, float alpha, glm::mat4 model)
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
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear(GLbitfield field)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Renderer::BindVertex(float* vertices, int sizeVertices, int* indices, int sizeIndices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeVertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * sizeIndices, indices, GL_STATIC_DRAW);
}

void Renderer::UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::SetShapeAttributes()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer::SetSpriteAttributes()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}