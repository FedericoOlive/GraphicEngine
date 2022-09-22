#include "Quad.h"

Quad::Quad(Renderer* renderer)
{
	this->renderer = renderer;
	sizeVertices = 24;
	sizeIndices = 6;

    vertices = new float[sizeVertices] {
        // positions          // colors
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // top left 
    };
	
    indices = new int[sizeIndices] {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
   

	renderer->BindVertex(vertices, sizeVertices, indices, sizeIndices, VAO, VBO, EBO);
	renderer->SetShapeAttributes();
}

Quad::~Quad()
{
    renderer->UnBindVertex(VAO, VBO, EBO);
    delete vertices;
    delete indices;
}