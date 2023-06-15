#ifndef CUBE_H
#define CUBE_H
#include "Entity/Entity3D.h"
#include "Entity/Entity2D/Texture.h"

class SAUCA_API Cube final : public Entity3D
{
public:
	Cube(Renderer* renderer);
	~Cube() override;
	void CreateVertexData() override;
	void Draw(Camera* camera) override;
	void SetTexture(Texture* texture, bool deleteExitingMaterial = true, bool deleteExitingTexture = true);
	void DeleteTextureAsociate();
	void SetTextureCoordinates(glm::vec2 topRight, glm::vec2 bottomRight, glm::vec2 bottomLeft, glm::vec2 topLeft);
protected:
	Texture* texture;
	void GenBufferEntity() override;
	void BindBufferEntity() override;
public:
	void RecalculateAABB() override;
};
#endif