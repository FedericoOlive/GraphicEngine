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
		2, 1, 0,
		0, 3, 2,

		// Back
		6, 5, 4,
		4, 7, 6,

		// Up
		10, 9, 8,
		8, 11, 10,

		// Down
		14, 13, 12,
		12, 15, 14,

		// Right
		18, 17, 16,
		16, 19, 18,

		// Left
		22, 21, 20,
		20, 23, 22
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

	for (auto iter = transform->childrens.begin(); iter != transform->childrens.end(); ++iter)
	{
		// todo: Draw Childrens
		// (*iter)->gameObject->ren
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

void Cube::OnAsigned()
{
	std::function<void()> recalculateAABB = [this] { RecalculateAABB(); };
	transform->OnUpdateModelMatrix.AddListener(recalculateAABB);
	RecalculateAABB();
}

void Cube::RecalculateAABB()
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