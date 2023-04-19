#include "Cube.h"

Cube::Cube(Renderer* renderer)
{
    SetRenderer(renderer);
    texture = nullptr;
    CreateVertexData();
	
    material = renderer->GetMaterialSolid();    // Todo: agregar la posibilidad de meter otro material
	
	isRenderizable = true;

    GenBufferEntity();
    BindBufferEntity();
}

Cube::~Cube()
{
    DeleteTextureAsociate();
    UnBindObject();
}

void Cube::CreateVertexData()
{
    vertexData = new VertexData();

    vertexData->sizeVertices = 72;
    vertexData->vertices = new float[vertexData->sizeVertices]{
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,

         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f
    };

    vertexData->sizeColor = 72;
    vertexData->colors = new float[vertexData->sizeColor]{
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    vertexData->sizeNormals = 72;
    vertexData->normals = new float[vertexData->sizeNormals]{
         0.0f,  0.0f,  -1.0f,
         0.0f,  0.0f,  -1.0f,
         0.0f,  0.0f,  -1.0f,
         0.0f,  0.0f,  -1.0f,

         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,

        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,

         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,

         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f
    };

    vertexData->sizeUvs = 48;
    vertexData->uvs = new float[vertexData->sizeUvs]{
        1.0f,  1.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,

        1.0f,  1.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,

        1.0f,  1.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,

        1.0f,  1.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,

        1.0f,  1.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,

        1.0f,  1.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,
    };

    vertexData->sizeIndex = 36;
    vertexData->indexes = new int[vertexData->sizeIndex]{
        0, 1, 3, // FRONT
        1, 2, 3,
        4, 5, 7, // BACK
        5, 6, 7,
        8, 9, 11, // LEFT  
        9, 10, 11,
        12, 13, 15, // BOTTOM
        13, 14, 15,
        16, 17, 19, // RIGHT 
        17, 18, 19,
        20, 21, 23, // TOP
        21, 22, 23
    };
}

void Cube::Draw()
{
    if (texture)
    {
        renderer->BindTextures(texture->texture);
        renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), texture->texture, material, alpha);
    }
    else
    {
		renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), NULL, material, alpha);	
    }
}

void Cube::SetTexture(Texture* texture)
{
    material = renderer->GetMaterialTexture();
    this->texture = texture;
}

void Cube::SetTextureCoordinates(glm::vec2 topRight, glm::vec2 bottomRight, glm::vec2 bottomLeft, glm::vec2 topLeft)
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

void Cube::DeleteTextureAsociate()
{
    if (texture != nullptr)
    {
        delete texture;
        texture = nullptr;
    }
}
void Cube::GenBufferEntity()
{
    GenBufferObject();	
    GenBufferVertex();
    GenBufferColor();
    GenBufferNormal();
    GenBufferTexture();
    GenBufferIndexes();
}

void Cube::BindBufferEntity()
{
    BindBufferVertex();
    BindBufferColors();
    BindBufferNormals();
    BindBufferTextures();
    BindBufferIndex();	
    UnBind();
}