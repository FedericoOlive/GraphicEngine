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
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
    };

    sizeIndices = 6;
    indices = new int[sizeIndices] {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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
        float currentUv[8] =
        {
            frame.coordinates[0].u,frame.coordinates[0].v,
            frame.coordinates[1].u,frame.coordinates[1].v,
            frame.coordinates[2].u,frame.coordinates[2].v,
            frame.coordinates[3].u,frame.coordinates[3].v,
        };

        vertices[6] = currentUv[0];
        vertices[7] = currentUv[1];
        vertices[14] = currentUv[2];
        vertices[15] = currentUv[3];
        vertices[22] = currentUv[4];
        vertices[23] = currentUv[5];
        vertices[30] = currentUv[6];
        vertices[31] = currentUv[7];

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

