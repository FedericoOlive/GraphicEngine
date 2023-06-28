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
	if (!material->hasTexture)
		glDisable(GL_CULL_FACE);
	
	renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), NULL, material, alpha, camera);
	
	if (!material->hasTexture)
		glEnable(GL_CULL_FACE);
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

void Triangle::OnAsigned()
{
	std::function<void()> recalculateAABB = [this] { RecalculateAABB(); };
	transform->OnUpdateModelMatrix.AddListener(recalculateAABB);
	RecalculateAABB();
}

void Triangle::RecalculateAABB()
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