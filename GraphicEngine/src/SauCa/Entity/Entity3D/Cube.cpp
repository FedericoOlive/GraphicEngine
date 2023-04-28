#include "Cube.h"

Cube::Cube(Renderer* renderer)
{
	name = "Cube";
	SetRenderer(renderer); 
	texture = nullptr;
	material = new Material(renderer->GetDefaultShader(), false);
	CreateVertexData();

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
	vertexData->vertices = new float[vertexData->sizeVertices] {
		// Front
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		// Back
		 0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,

		// Up
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		// Down
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,

		// Right
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,

		// Left
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	vertexData->sizeColor = 72;
	vertexData->colors = new float[vertexData->sizeColor] {
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
	vertexData->normals = new float[vertexData->sizeNormals] {
		 0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,

		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,

		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,

		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,

		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f
	};

	vertexData->sizeUvs = 48;
	vertexData->uvs = new float[vertexData->sizeUvs] {
		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f
	};

	vertexData->sizeIndex = 36;
	vertexData->indexes = new int[vertexData->sizeIndex] {
		// Front
		0, 1, 2,
		2, 3, 0,

		// Back
		4, 5, 6,
		6, 7, 4,

		// Up
		8, 9, 10,
		10, 11, 8,

		// Down
		12, 13, 14,
		14, 15, 12,

		// Right
		16, 17, 18,
		18, 19, 16,

		// Left
		20, 21, 22,
		22, 23, 20
	};
}

void Cube::Draw(Camera* camera)
{
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

void Cube::SetTexture(Texture* texture, bool deleteExitingMaterial, bool deleteExitingTexture)
{
	if (deleteExitingMaterial && material != nullptr)
		delete material;
	if (deleteExitingTexture && this->texture != nullptr)
		delete this->texture;

	material = new Material(renderer->GetDefaultShader(), true);
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