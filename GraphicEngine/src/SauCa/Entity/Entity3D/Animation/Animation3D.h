#ifndef ANIMATION3D_H
#define ANIMATION3D_H

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "Entity/Entity3D/Model.h"

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class SAUCA_API Animation3D
{
public:
	Animation3D() = default;
	Animation3D(const std::string& animationPath, Model* model);
	~Animation3D();
	Bone* FindBone(const std::string& name);
	float GetTicksPerSecond() const;
	float GetDuration() const;
	const AssimpNodeData& GetRootNode() const;
	const std::map<std::string, BoneInfo>& GetBoneIDMap() const;
private:
	void ReadMissingBones(const aiAnimation* animation, Model& model);
	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);
	float m_Duration;
	int m_TicksPerSecond;
	std::vector<Bone> m_Bones;
	AssimpNodeData m_RootNode;
	std::map<std::string, BoneInfo> m_BoneInfoMap;
};

#endif