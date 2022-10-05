#include "Sprite.h"

Sprite::Sprite(Texture* texture, Renderer* renderer)
{
    this->texture = texture->texture;
	
    this->renderer = renderer;
    sizeVertices = 32;
	
    vertices = new float[sizeVertices] {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    sizeIndices = 6;
    indices = new int[sizeIndices] {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };


    renderer->BindVertex(vertices, sizeVertices, indices, sizeIndices, VAO, VBO, EBO);
    renderer->SetSpriteAttributes();    
}

void Sprite::Draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    renderer->DrawSprite(texture, sizeIndices, VAO, colorTint, modelMatrix);
}

Sprite::~Sprite()
{
	
}