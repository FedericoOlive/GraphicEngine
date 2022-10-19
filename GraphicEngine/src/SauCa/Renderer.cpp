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
    viewMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::mat4(1.0f);
    glewExperimental = GL_TRUE;
    glewInit();
    shader = new Shader(true); // you can name your shader files however you like
    shaderTexture = new Shader(false); // you can name your shader files however you like
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DrawShape(int sizeIndices, unsigned int& VAO, glm::vec3 color, float alpha, glm::mat4 model)
{
    shader->Use();
	
    unsigned int locationColor = glGetUniformLocation(shader->ID, "colorTint");
    unsigned int locationAlpha = glGetUniformLocation(shader->ID, "alpha");
    unsigned int modelLoc = glGetUniformLocation(shader->ID, "modelMatrix");
    unsigned int viewLoc = glGetUniformLocation(shader->ID, "viewMatrix");
    unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projectionMatrix");
	
    glUniform3fv(locationColor, 1, value_ptr(color));
    glUniform1fv(locationAlpha, 1, &alpha);	
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawSprite(unsigned int textureID, int sizeIndices, unsigned int& VAO, glm::vec3 color, float alpha, glm::mat4 model)
{
    shaderTexture->Use();
	
    unsigned int locationTexture = glGetUniformLocation(shaderTexture->ID, "ourTexture");
    unsigned int locationColor = glGetUniformLocation(shaderTexture->ID, "colorTint");
    unsigned int locationAlpha = glGetUniformLocation(shaderTexture->ID, "alpha");
    unsigned int transformLoc = glGetUniformLocation(shaderTexture->ID, "modelMatrix");
    unsigned int viewLoc = glGetUniformLocation(shaderTexture->ID, "viewMatrix");
    unsigned int projectionLoc = glGetUniformLocation(shaderTexture->ID, "projectionMatrix");
	
    glUniform1f(locationTexture, (GLfloat)textureID);
    glUniform3fv(locationColor, 1, value_ptr(color));
    glUniform1fv(locationAlpha, 1, &alpha);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, nullptr);
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