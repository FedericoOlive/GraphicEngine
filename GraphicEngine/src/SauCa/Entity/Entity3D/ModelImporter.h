#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <map>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

#include "Entity/Entity2D/stbi.h"
#include "Mesh.h"
#include "Animation/Bone.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool IsInvertTextures, bool gamma = false);

class SAUCA_API ModelImporter
{
public:
	static void LoadModel(std::string const& path, std::string& directory, std::vector<Mesh>& meshes, std::vector<MeshTexture>& textures_loaded, bool& IsInvertTextures, std::map<std::string, BoneInfo>& m_BoneInfoMap, int& m_BoneCounter);
	static void ProcessNode(aiNode* node, const aiScene* scene, std::string& directory, std::vector<Mesh>& meshes, std::vector<MeshTexture>& textures_loaded, bool& IsInvertTextures, std::map<std::string, BoneInfo>& m_BoneInfoMap, int& m_BoneCounter);
	static void SetVertexBoneDataToDefault(Vertex& vertex);
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<MeshTexture>& textures_loaded, std::string& directory, bool& IsInvertTextures, std::map<std::string, BoneInfo>& m_BoneInfoMap, int& m_BoneCounter);
	static void SetVertexBoneData(Vertex& vertex, int& boneID, float& weight);
	static void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene, std::map<std::string, BoneInfo>& m_BoneInfoMap, int& m_BoneCounter);
	static std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::vector<MeshTexture>& textures_loaded, std::string& directory, bool& IsInvertTextures);
};

#endif