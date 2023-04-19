#include "Entity.h"

#include "CollisionManager.h"

Entity::Entity() : Component()
{
	vertexData = nullptr;
	isRenderizable = true;	
	alpha = 1.0f;
}

Entity::~Entity()
{
	delete vertexData;
}

void Entity::SetRenderer(Renderer* renderer)
{
	this->renderer = renderer;
}

void Entity::SetColorTint(float r, float g, float b, float a)
{
	material->colorTint = glm::vec3(r, g, b);
	alpha = a;
}

void Entity::BindBufferVertex(int modeDataStore)
{
	renderer->BindBufferData(vertexData->VBO, vertexData->atribVertex, vertexData->atribVertexSize, vertexData->sizeVertices, vertexData->vertices, modeDataStore);
}

void Entity::BindBufferColors(int modeDataStore)
{
	renderer->BindBufferData(vertexData->COL, vertexData->atribColor, vertexData->atribColorSize, vertexData->sizeColor, vertexData->colors, modeDataStore);
}

void Entity::BindBufferNormals(int modeDataStore)
{
	renderer->BindBufferData(vertexData->LVAO, vertexData->atribNormal, vertexData->atribNormalSize, vertexData->sizeNormals, vertexData->normals, modeDataStore);
}

void Entity::BindBufferTextures(int modeDataStore)
{
	renderer->BindBufferData(vertexData->UVB, vertexData->atribUvs, vertexData->atribUvsSize, vertexData->sizeUvs, vertexData->uvs, modeDataStore);
}

void Entity::BindBufferIndex()
{
	renderer->BindIndex(vertexData->EBO, vertexData->sizeIndex, vertexData->indexes);
}