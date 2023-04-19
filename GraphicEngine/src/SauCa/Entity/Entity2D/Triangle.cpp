#include "Triangle.h"

Triangle::Triangle(Renderer* renderer)
{
	material = renderer->GetMaterialSolid();
	SetRenderer(renderer);
	CreateVertexData();

	Triangle::GenBufferEntity();
	Triangle::BindBufferEntity();
}

Triangle::~Triangle()
{
	UnBindObject();
}

void Triangle::CreateVertexData()
{
	vertexData = new VertexData();

	vertexData->sizeVertices = 9;
	vertexData->vertices = new float[vertexData->sizeVertices]{
		 0.5f, -0.5f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		// bottom left
		 0.0f,  0.5f, 0.0f,		// top 
	};

	vertexData->sizeColor = 9;
	vertexData->colors = new float[vertexData->sizeColor]{
		 0.5f, -0.5f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		// bottom left
		 0.0f,  0.5f, 0.0f,		// top 
	};

	vertexData->sizeNormals = 9;
	vertexData->normals = new float[vertexData->sizeNormals]{
		0.0f, 0.0f, -1.0f,		// bottom right
		0.0f, 0.0f, -1.0f,		// bottom left
		0.0f, 0.0f, -1.0f,		// top 
	};

	vertexData->sizeIndex = 3;
	vertexData->indexes = new int[vertexData->sizeIndex]{
		0, 1, 2
	};
}

void Triangle::Draw()
{
	renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), NULL, material, alpha);
}

void Triangle::GenBufferEntity()
{
	GenBufferObject();
	GenBufferVertex();
	GenBufferColor();
	GenBufferNormal();
	GenBufferIndexes();
}

void Triangle::BindBufferEntity()
{
	BindBufferVertex();
	BindBufferColors();
	BindBufferNormals();
	BindBufferIndex();
	UnBind();
}