#ifndef ENTITY_H
#define ENTITY_H

#include "Renderer.h"
#include "Entity2D/Material.h"
#include "GameObjects/GameObject.h"
#include "VertexData.h"

class SAUCA_API Entity : public Component
{
private:

public:
	float alpha;
	Material* material;
	int layerRender = 0;

	Entity();
	~Entity();
	virtual void CreateVertexData() {}
	void SetRenderer(Renderer* renderer);

	void SetColorTint(float r, float g, float b, float a);
	void SetColorTint(glm::vec4 tint) { SetColorTint(tint.r, tint.g, tint.b, tint.a); }

protected:
	VertexData* vertexData;
	Renderer* renderer;
		
	virtual void GenBufferEntity() {}
	virtual void BindBufferEntity() {}

	void GenBufferObject()	const { renderer->BindGenBufferObject(vertexData->VAO); }
	void UnBind()			const { renderer->UnBindGenBufferObject(); }
	void UnBindObject()		const { renderer->UnBindObject(vertexData->VAO, vertexData->VBO, vertexData->COL, vertexData->LVAO, vertexData->UVB, vertexData->EBO); }
	void GenBufferVertex()	const { renderer->GenBuffer(1, vertexData->VBO); }
	void GenBufferColor()	const { renderer->GenBuffer(1, vertexData->COL); }
	void GenBufferNormal()	const { renderer->GenBuffer(1, vertexData->LVAO); }
	void GenBufferTexture()	const { renderer->GenBuffer(1, vertexData->UVB); }
	void GenBufferIndexes()	const { renderer->GenBuffer(1, vertexData->EBO); }

	void BindBufferVertex(int modeDataStore = 0)	const { renderer->BindBufferData(vertexData->VBO, vertexData->atribVertex, vertexData->atribVertexSize, vertexData->sizeVertices, vertexData->vertices, modeDataStore); }
	void BindBufferColors(int modeDataStore = 0)	const { renderer->BindBufferData(vertexData->COL, vertexData->atribColor, vertexData->atribColorSize, vertexData->sizeColor, vertexData->colors, modeDataStore); }
	void BindBufferNormals(int modeDataStore = 0)	const { renderer->BindBufferData(vertexData->LVAO, vertexData->atribNormal, vertexData->atribNormalSize, vertexData->sizeNormals, vertexData->normals, modeDataStore); }
	void BindBufferTextures(int modeDataStore = 0)	const { renderer->BindBufferData(vertexData->UVB, vertexData->atribUvs, vertexData->atribUvsSize, vertexData->sizeUvs, vertexData->uvs, modeDataStore); }
	void BindBufferIndex()							const { renderer->BindIndex(vertexData->EBO, vertexData->sizeIndex, vertexData->indexes); }
};

#endif