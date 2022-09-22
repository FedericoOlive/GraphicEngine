#include "Renderer.h"

using namespace std;

Renderer::Renderer()
{
    shader = nullptr;
}

Renderer::~Renderer()
{
    delete shader;
}

void Renderer::CreateShader()
{
    shader = new Shader(true); // you can name your shader files however you like
    shaderTexture = new Shader(false); // you can name your shader files however you like
}

void Renderer::DrawShape(int sizeIndices, unsigned int& VAO)
{
    shader->Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawSprite(unsigned int textureID, int sizeIndices, unsigned int& VAO)
{
    //glActiveTexture(GL_TEXTURE0);
    shaderTexture->Use();
    int uniform = glGetUniformLocation(shaderTexture->ID, "ourTexture");
    glUniform1i(uniform, 0); // Todo: Ver porque 0
    //shaderTexture->SetFloat("ourTexture", 1);
	
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);
}

void Renderer::Clear(GLbitfield field)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Renderer::UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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