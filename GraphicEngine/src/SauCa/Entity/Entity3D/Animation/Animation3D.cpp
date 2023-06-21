#include "Animation3D.h"
#include <functional>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Animation3D::Animation3D(const std::string& animationPath, Model* model)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	auto animation = scene->mAnimations[0];
	m_Duration = animation->mDuration;
	m_TicksPerSecond = animation->mTicksPerSecond;
	aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
	globalTransformation = globalTransformation.Inverse();
	ReadHierarchyData(m_RootNode, scene->mRootNode);
	ReadMissingBones(animation, *model);
}

Animation3D::~Animation3D() { }

Bone* Animation3D::FindBone(const std::string& name)
{
	auto iter = std::find_if(m_Bones.begin(), m_Bones.end(), [&](const Bone& Bone)
		{
			return Bone.GetBoneName() == name;
		});
	
	if (iter == m_Bones.end())
		return nullptr;
	else
		return &(*iter);
}

float Animation3D::GetTicksPerSecond() const { return m_TicksPerSecond; }
float Animation3D::GetDuration() const { return m_Duration; }
const AssimpNodeData& Animation3D::GetRootNode() const { return m_RootNode; }
const std::map<std::string, BoneInfo>& Animation3D::GetBoneIDMap() const { return m_BoneInfoMap; }

void Animation3D::ReadMissingBones(const aiAnimation* animation, Model& model)
{
	int size = animation->mNumChannels;

	auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from Model class
	int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model class

	//reading channels(bones engaged in an animation and their keyframes)
	for (int i = 0; i < size; i++)
	{
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		if (boneInfoMap.find(boneName) == boneInfoMap.end())
		{
			boneInfoMap[boneName].id = boneCount;
			boneCount++;
		}
		m_Bones.push_back(Bone(channel->mNodeName.data,
		                       boneInfoMap[channel->mNodeName.data].id, channel));
	}

	m_BoneInfoMap = boneInfoMap;
}

void Animation3D::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
	assert(src);

	dest.name = src->mName.data;
	dest.transformation = Utility::ConvertMatrixToGLMFormat(src->mTransformation);
	dest.childrenCount = src->mNumChildren;

	for (int i = 0; i < src->mNumChildren; i++)
	{
		AssimpNodeData newData;
		ReadHierarchyData(newData, src->mChildren[i]);
		dest.children.push_back(newData);
	}
}
