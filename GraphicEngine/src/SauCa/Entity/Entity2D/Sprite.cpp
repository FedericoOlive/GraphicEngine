#include "Sprite.h"
#include "Timer.h"

Sprite::Sprite(Texture* texture, Renderer* renderer)
{
    material = renderer->GetMaterialTexture();
    hasAnimation = false;
    SetTexture(texture);

    this->renderer = renderer;
    sizeVertices = 32;

    vertices = new float[sizeVertices] {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
    };

    sizeIndices = 6;
    indices = new int[sizeIndices] {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    renderer->BindVertex(vertices, sizeVertices, indices, sizeIndices, VAO, VBO, EBO);
    renderer->SetSpriteAttributes();
}

Sprite::~Sprite() 
{ 
    while (!animations.empty()) 
    {
        delete animations.back();
        animations.pop_back();
    }
}

void Sprite::Draw(int anim )
{
    if (hasAnimation) 
    {
        animations[anim]->Update();

        frame = animations[anim]->GetFrames()[animations[anim]->CurrentFrame()];
        SetTextureCoordinates(
            { frame.coordinates[0].u, frame.coordinates[0].v },
            { frame.coordinates[1].u, frame.coordinates[1].v },
            { frame.coordinates[2].u, frame.coordinates[2].v },
            { frame.coordinates[3].u, frame.coordinates[3].v });

        renderer->BindVertexs(vertices, sizeVertices, indices, sizeIndices, VAO, VBO, EBO);
        renderer->SetSpriteAttributes();
    }

    renderer->BindTextures(texture->texture);
    renderer->DrawEntity2D(texture->texture, sizeIndices, VAO, material, alpha, modelMatrix);
}

void Sprite::SetTexture(Texture* texture)
{
    this->texture = texture;
}

void Sprite::DeleteTextureAsociate()
{
    if (texture != nullptr)
    {
        delete texture;
        texture = nullptr;
    }
}

void Sprite::AddAnimation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs)
{
    glGenBuffers(1, &UVBuffer);
    hasAnimation = true;
    animations.push_back(new Animation(frameX, frameY, frameWidth, frameHeigth, textureWidth, textureHeigth, durationInSecs));
}

void Sprite::AddAnimation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs, int frameCount)
{
    glGenBuffers(1, &UVBuffer);
    hasAnimation = true;
    animations.push_back(new Animation(frameX, frameY, frameWidth, frameHeigth, textureWidth, textureHeigth, durationInSecs,frameCount));
}

std::vector<Animation*> Sprite::GetAnimations()
{
    return animations;
}

void Sprite::SetTextureCoordinates(glm::vec2 topRight, glm::vec2 bottomRight, glm::vec2 bottomLeft, glm::vec2 topLeft)
{
    vertices[6] = topRight.x;
    vertices[7] = topRight.y;

    vertices[14] = bottomRight.x;
    vertices[15] = bottomRight.y;

    vertices[22] = bottomLeft.x;
    vertices[23] = bottomLeft.y;

    vertices[30] = topLeft.x;
    vertices[31] = topLeft.y;
}