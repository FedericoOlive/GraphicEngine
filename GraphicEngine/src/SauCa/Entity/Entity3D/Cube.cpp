#include "Cube.h"

Cube::Cube(Renderer* renderer)
{
    this->renderer = renderer;
    material = renderer->GetMaterialSolid();
	
	isRenderizable = true;

    sizeVertices = 192;
    vertices = new float[sizeVertices] {
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, -1.0f,
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, -1.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, -1.0f,
        -0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, -1.0f,
    	                                               
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
    	                                               
        -0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
    	                                               
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
    	                                               
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,
    	                                               
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     -1.0f, 0.0f
    };

    sizeIndices = 36;
    indices = new int[sizeIndices] {
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

    renderer->BindVertex(vertices, sizeVertices, indices, sizeIndices, VAO, VBO, EBO);
    renderer->SetSpriteAttributes();
}

Cube::~Cube()
{
	
}

void Cube::Draw()
{
	renderer->DrawEntity2D(NULL, sizeIndices, VAO, material, alpha, transform->GetModelMatrix());
}

void Cube::Update()
{
	
}

void Cube::Input()
{
	
}

void Cube::OnAsigned()
{
	
}