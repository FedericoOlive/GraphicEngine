#pragma once
#include "Entity/Entity2D/Shape.h"

class SAUCA_API Quad : public Shape
{
public:
	Quad(Renderer* renderer);
	Quad(Renderer* renderer, Material* mat);
	~Quad();
	void CreateVertexData() override;
	void GenBufferEntity() override;
	void BindBufferEntity() override;
};