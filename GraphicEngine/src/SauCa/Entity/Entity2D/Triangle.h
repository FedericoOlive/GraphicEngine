#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class SAUCA_API Triangle final : public Shape
{
public:
	Triangle(Renderer* renderer, bool setAsIcon = false);
	~Triangle();
	void CreateVertexData() override;
	void Draw(Camera* camera) override;
	void GenBufferEntity() override;
	void BindBufferEntity() override;

	void OnAsigned() override;
	void RecalculateAABB() override;
};

#endif