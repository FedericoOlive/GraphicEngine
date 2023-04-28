#include "Sprite.h"
#include "Timer.h"

Sprite::Sprite()
{
    name = "Sprite";
    material = new Material(renderer->GetDefaultShader(), false);
    Sprite::CreateVertexData();
}

Sprite::Sprite(Texture* texture, Renderer* renderer, bool deleteExistingMaterial)
{
    name = "Sprite";
    if (deleteExistingMaterial && material != nullptr)
        delete material;
    material = new Material(renderer->GetDefaultShader(), true);
    hasAnimation = false;
    SetTexture(texture);

    SetRenderer(renderer);
    Sprite::CreateVertexData();

    Sprite::GenBufferEntity();
    Sprite::BindBufferEntity();
}

Sprite::~Sprite() 
{ 
    while (!animations.empty()) 
    {
        delete animations.back();
        animations.pop_back();
    }
    renderer->UnBindObject(vertexData->VAO, vertexData->VBO, vertexData->COL, vertexData->LVAO, vertexData->UVB, vertexData->EBO);
}

void Sprite::CreateVertexData()
{
    vertexData = new VertexData();
	
    vertexData->sizeVertices = 12;
    vertexData->vertices = new float[vertexData->sizeVertices]{
        // Positions      
        0.5f,  0.5f, 0.0f,  // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
       -0.5f, -0.5f, 0.0f,  // Bottom Left
       -0.5f,  0.5f, 0.0f   // Top Left 
    };
    vertexData->sizeColor = 12;
    vertexData->colors = new float[vertexData->sizeColor]{
        // Colors        
        1.0f, 1.0f, 1.0f,   // Top Right
        1.0f, 1.0f, 1.0f,   // Bottom Right
        1.0f, 1.0f, 1.0f,   // Bottom Left
        1.0f, 1.0f, 1.0f    // Top Left 
    };

    vertexData->sizeNormals = 12;
    vertexData->normals = new float[vertexData->sizeNormals]{
        // Normals        
        0.0f, 0.0f, 1.0f,  // Top Right
        0.0f, 0.0f, 1.0f,  // Bottom Right
        0.0f, 0.0f, 1.0f,  // Bottom Left
        0.0f, 0.0f, 1.0f   // Top Left 
    };

    vertexData->sizeUvs = 8;
    vertexData->uvs = new float[vertexData->sizeUvs]{
        // Coords
        1.0f, 1.0f,         // Top Right
        1.0f, 0.0f,         // Bottom Right
        0.0f, 0.0f,         // Bottom Left
        0.0f, 1.0f          // Top Left 
    };

    vertexData->sizeIndex = 6;
    vertexData->indexes = new int[vertexData->sizeIndex]{
        0, 1, 3,            // First Triangle
        1, 2, 3             // Second Triangle
    };
}

void Sprite::Draw(Camera* camera)
{
    if (hasAnimation)
    {
        animations[currentAnim]->Update();

        frame = animations[currentAnim]->GetFrames()[animations[currentAnim]->CurrentFrame()];
        SetTextureCoordinates(
            { frame.coordinates[0].u, frame.coordinates[0].v },
            { frame.coordinates[1].u, frame.coordinates[1].v },
            { frame.coordinates[2].u, frame.coordinates[2].v },
            { frame.coordinates[3].u, frame.coordinates[3].v });
    }

    if (texture)
    {
        renderer->BindTextures(texture->texture);
        renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), texture->texture, material, alpha, camera);
    }
    else
    {
        renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), NULL, material, alpha, camera);
    }
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
    //glGenBuffers(1, &vertexData->UVB);
    hasAnimation = true;
    animations.push_back(new Animation(frameX, frameY, frameWidth, frameHeigth, textureWidth, textureHeigth, durationInSecs));
}

void Sprite::AddAnimation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs, int frameCount)
{
    //glGenBuffers(1, &vertexData->UVB);
    hasAnimation = true;
    animations.push_back(new Animation(frameX, frameY, frameWidth, frameHeigth, textureWidth, textureHeigth, durationInSecs,frameCount));
}

std::vector<Animation*> Sprite::GetAnimations()
{
    return animations;
}

void Sprite::SetTextureCoordinates(glm::vec2 topRight, glm::vec2 bottomRight, glm::vec2 bottomLeft, glm::vec2 topLeft)
{
    vertexData->uvs[0] = topRight.x;
    vertexData->uvs[1] = topRight.y;
    
    vertexData->uvs[2] = bottomRight.x;
    vertexData->uvs[3] = bottomRight.y;
    
    vertexData->uvs[4] = bottomLeft.x;
    vertexData->uvs[5] = bottomLeft.y;
    
    vertexData->uvs[6] = topLeft.x;
    vertexData->uvs[7] = topLeft.y;

    BindBufferTextures(1);
}

void Sprite::GenBufferEntity()
{
    GenBufferObject();
    GenBufferVertex();
    GenBufferColor();
    GenBufferNormal();
    GenBufferTexture();
    GenBufferIndexes();
}

void Sprite::BindBufferEntity()
{
    BindBufferVertex();
    BindBufferColors();
    BindBufferNormals();
    BindBufferTextures();
    BindBufferIndex();
    UnBind();
}