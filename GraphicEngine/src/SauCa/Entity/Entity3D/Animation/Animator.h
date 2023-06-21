#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <glm/glm.hpp>
#include <vector>
#include "Exports.h"
#include "Animation3D.h"

class SAUCA_API Animator
{
public:
	Animator(Animation3D* animation);
	void UpdateAnimation(float dt);
	void PlayAnimation(Animation3D* pAnimation);
	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
	std::vector<glm::mat4> GetFinalBoneMatrices() const;
	
private:
	std::vector<glm::mat4> m_FinalBoneMatrices;
	Animation3D* m_CurrentAnimation;
	float m_CurrentTime;
	float m_DeltaTime;
};

#endif