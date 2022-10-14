#include "Triangle.h"

Triangle::Triangle(Renderer* renderer)
{
	this->renderer = renderer;
	sizeVertices = 18;
	sizeIndices = 3;
	
	vertices = new float[sizeVertices] {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f   // top 
	};

	indices = new int[sizeIndices] {0, 1, 2};

	renderer->BindVertex(vertices, sizeVertices, indices, sizeIndices, VAO, VBO, EBO);
	renderer->SetShapeAttributes();
}

Triangle::~Triangle()
{
	renderer->UnBindVertex(VAO, VBO, EBO);
	delete vertices;
	delete indices;
}