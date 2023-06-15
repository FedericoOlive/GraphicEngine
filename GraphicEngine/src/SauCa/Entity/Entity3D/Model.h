#ifndef MODEL_H
#define MODEL_H


#include <string>
#include <vector>

#include "Mesh.h"
#include "Entity/Entity3D.h"


class SAUCA_API Model : public Entity3D
{
public:
	std::vector<MeshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    Model(Renderer* renderer, std::string const& path, bool isInvertIndexesOrder, bool isInvertTextures);
	~Model() override;
	void CreateVertexData() override;
	void Draw(Camera* camera) override;
	void GenBufferEntity() override;
	void BindBufferEntity() override;
	void RecalculateAABB() override;
private:
	bool isInvertIndexesOrder = false;
};

#endif