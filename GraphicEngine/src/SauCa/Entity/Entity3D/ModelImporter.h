#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include "Entity/Entity2D/stbi.h"
#include <assimp/scene.h>
#include "Mesh.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool IsInvertTextures, bool gamma = false);

class SAUCA_API ModelImporter
{
private:
public:
	static void LoadModel(std::string const& path, std::string& directory, std::vector<Mesh>& meshes, std::vector<MeshTexture>& textures_loaded, bool& IsInvertTextures);
	static void ProcessNode(aiNode* node, const aiScene* scene, std::string& directory, std::vector<Mesh>& meshes, std::vector<MeshTexture>& textures_loaded, bool& IsInvertTextures);
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<MeshTexture>& textures_loaded, std::string& directory, bool& IsInvertTextures);
	static std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::vector<MeshTexture>& textures_loaded, std::string& directory, bool& IsInvertTextures);
};

#endif