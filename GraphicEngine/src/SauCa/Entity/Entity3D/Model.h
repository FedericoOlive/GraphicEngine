#ifndef MODEL_H
#define MODEL_H

#include "Entity/Entity2D/stbi.h"
#include <assimp/scene.h>

#include <string>
#include <vector>

#include "Mesh.h"
#include "Entity/Entity3D.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool IsInvertTextures, bool gamma = false);

class SAUCA_API Model : public Entity3D
{
public:
	std::vector<MeshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    Model(Renderer* renderer, std::string const& path, bool isInvertIndexesOrder, bool IsInvertTextures);
	~Model() override;
	void CreateVertexData() override;
	void Draw(Camera* camera) override;
	void GenBufferEntity() override;
	void BindBufferEntity() override;

private:
	bool isInvertIndexesOrder = false;
	bool IsInvertTextures = false;
	void loadModel(std::string const& path);
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif