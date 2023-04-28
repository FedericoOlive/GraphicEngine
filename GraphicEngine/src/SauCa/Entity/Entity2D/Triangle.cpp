#include "Triangle.h"

Triangle::Triangle(Renderer* renderer, bool setAsIcon)
{
	name = "Triangle";
	if (setAsIcon)
		material = new Material(renderer->GetDefaultShaderSolid(), false);
	else
		material = new Material(renderer->GetDefaultShader(), false);
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
		 0.5f, 0.0f,  0.5f, 	// bottom right
		-0.5f, 0.0f,  0.5f, 	// bottom left
		 0.0f, 0.0f, -0.5f		// top 
	};

	vertexData->sizeColor = 9;
	vertexData->colors = new float[vertexData->sizeColor]{
		1.0f, 0.0f, 0.0f,		// bottom right
		0.0f, 0.0f, 1.0f,		// bottom left
		1.0f, 1.0f, 1.0f		// top 
	};

	vertexData->sizeNormals = 9;
	vertexData->normals = new float[vertexData->sizeNormals]{
		0.0f, 1.0f, 0.0f,		// bottom right
		0.0f, 1.0f, 0.0f,		// bottom left
		0.0f, 1.0f, 0.0f		// top 
	};

	vertexData->sizeIndex = 3;
	vertexData->indexes = new int[vertexData->sizeIndex]{
		0, 1, 2
	};
}

void Triangle::Draw(Camera* camera)
{
	renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), NULL, material, alpha, camera);
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