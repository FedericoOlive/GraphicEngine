#include "Quad.h"

Quad::Quad(Renderer* renderer)
{
    name = "Quad";
    SetRenderer(renderer);
    material = new Material(renderer->GetDefaultShader(), false);
    Quad::CreateVertexData();

    Quad::GenBufferEntity();
    Quad::BindBufferEntity();
}

Quad::Quad(Renderer* renderer, Material* mat)
{
    material = mat;
    SetRenderer(renderer);
    Quad::CreateVertexData();

    Quad::GenBufferEntity();
    Quad::BindBufferEntity();
}

Quad::~Quad()
{
    UnBindObject();
}

void Quad::CreateVertexData()
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
        1.0f, 1.0f, 1.0f,    // Top Right
        1.0f, 1.0f, 1.0f,    // Bottom Right
        1.0f, 1.0f, 1.0f,    // Bottom Left
        1.0f, 1.0f, 1.0f     // Top Left 
    };

    vertexData->sizeNormals = 12;
    vertexData->normals = new float[vertexData->sizeNormals]{
        // Normals        
        0.0f, 0.0f, -1.0f,    // Top Right
        0.0f, 0.0f, -1.0f,    // Bottom Right
        0.0f, 0.0f, -1.0f,    // Bottom Left
        0.0f, 0.0f, -1.0f     // Top Left 
    };

    vertexData->sizeIndex = 6;
    vertexData->indexes = new int[vertexData->sizeIndex]{
        0, 1, 3,              // First Triangle
        1, 2, 3               // Second Triangle
    };
}

void Quad::GenBufferEntity()
{
    GenBufferObject();
    GenBufferVertex();
    GenBufferColor();
    GenBufferNormal();
    GenBufferIndexes();    
}

void Quad::BindBufferEntity()
{
    BindBufferVertex();
    BindBufferColors();
    BindBufferNormals();
    BindBufferIndex();
    UnBind();
}

void Quad::OnAsigned()
{
    std::function<void()> recalculateAABB = [this] { RecalculateAABB(); };
    transform->OnUpdateModelMatrix.AddListener(recalculateAABB);
    RecalculateAABB();
}

void Quad::RecalculateAABB()
{
    transform->aabbGlobal->BeforeUpdate();

    int i = 0;
    while (i < vertexData->sizeVertices)
    {
        glm::vec3 modelVertex = (transform->GetModelMatrix() * glm::vec4(vertexData->vertices[i], vertexData->vertices[i + 1], vertexData->vertices[i + 2], 1.0f));
        i += 3;

        transform->aabbGlobal->min.x = glm::min(transform->aabbGlobal->min.x, modelVertex.x);
        transform->aabbGlobal->max.x = glm::max(transform->aabbGlobal->max.x, modelVertex.x);
        transform->aabbGlobal->min.y = glm::min(transform->aabbGlobal->min.y, modelVertex.y);
        transform->aabbGlobal->max.y = glm::max(transform->aabbGlobal->max.y, modelVertex.y);
        transform->aabbGlobal->min.z = glm::min(transform->aabbGlobal->min.z, modelVertex.z);
        transform->aabbGlobal->max.z = glm::max(transform->aabbGlobal->max.z, modelVertex.z);
    }

    transform->aabbGlobal->AfterUpdate();

    transform->aabbLocal->min = transform->aabbGlobal->min;
    transform->aabbLocal->max = transform->aabbGlobal->max;
    transform->aabbLocal->AfterUpdate();
	
    CalculateParentAABB();
}