#ifndef ENTITY_H
#define ENTITY_H

#include "Renderer.h"
#include "Entity2D/Material.h"
#include "GameObjects/GameObject.h"
#include "VertexData.h"

class SAUCA_API Entity : public Component
{
protected:
	Renderer* renderer;
	VertexData* vertexData;

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
	virtual void GenBufferEntity() {}
	virtual void BindBufferEntity() {}
	
	void GenBufferObject()	const { renderer->BindGenBufferObject(vertexData->VAO); }
	void UnBind()			const { renderer->UnBindGenBufferObject(); }
	void GenBufferVertex()	const { renderer->GenBuffer(1, vertexData->VBO); }
	void GenBufferColor()	const { renderer->GenBuffer(1, vertexData->COL); }
	void GenBufferNormal()	const { renderer->GenBuffer(1, vertexData->LVAO); }
	void GenBufferTexture()	const { renderer->GenBuffer(1, vertexData->UVB); }
	void GenBufferIndexes()	const { renderer->GenBuffer(1, vertexData->EBO); }

	void BindBufferVertex(int modeDataStore = 0);
	void BindBufferColors(int modeDataStore = 0);
	void BindBufferNormals(int modeDataStore = 0);
	void BindBufferTextures(int modeDataStore = 0);
	void BindBufferIndex();
};

#endif