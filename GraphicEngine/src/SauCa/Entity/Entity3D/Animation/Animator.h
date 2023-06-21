#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <glm/glm.hpp>
#include <vector>
#include "Exports.h"
#include "Animation3D.h"
#include "GameObjects/Transform.h"

class SAUCA_API Animator
{
public:
	std::vector<glm::mat4> m_FinalBoneMatrices;
	
	Animator(Animation3D* animation, Transform* transform);
	void UpdateAnimation(float dt);
	void PlayAnimation(Animation3D* pAnimation);
	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
	std::vector<glm::mat4> GetFinalBoneMatrices() const;
private:
	Transform* transform;
	Animation3D* m_CurrentAnimation;
	float m_CurrentTime;
	float m_DeltaTime;
};

#endif