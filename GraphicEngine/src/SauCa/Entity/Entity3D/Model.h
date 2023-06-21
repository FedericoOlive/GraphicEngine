#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>
#include <vector>
#include "ModelImporter.h"
#include "Animation/Animator.h"
#include "Entity/Entity3D.h"

class SAUCA_API Model : public Entity3D
{
public:
	Animator* animator = nullptr;
	std::vector<Animation3D*> animations;
	std::vector<MeshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
	auto& GetBoneInfoMap() { return m_BoneInfoMap; }
	int& GetBoneCount() { return m_BoneCounter; }

    Model(Renderer* renderer, std::string const& path, bool isInvertIndexesOrder, bool isInvertTextures);
	~Model() override;
	void CreateVertexData() override;
	void Update(double deltaTime) override;
	void Draw(Camera* camera) override;
	void GenBufferEntity() override;
	void BindBufferEntity() override;
	void OnAsigned() override;
	void RecalculateAABB() override;
	Animation3D* CreateAnimation(const std::string& animationPath);
	void CreateAnimator(Animation3D* animation);
private:
	bool isInvertIndexesOrder = false;
	std::map<std::string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;
};

#endif