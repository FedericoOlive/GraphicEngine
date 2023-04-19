#include "Quad.h"

Quad::Quad(Renderer* renderer)
{
    SetRenderer(renderer);
    material = renderer->GetMaterialSolid();
    CreateVertexData();

    Quad::GenBufferEntity();
    Quad::BindBufferEntity();
}

Quad::Quad(Renderer* renderer, Material* mat)
{
    material = mat;
    SetRenderer(renderer);
    CreateVertexData();

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