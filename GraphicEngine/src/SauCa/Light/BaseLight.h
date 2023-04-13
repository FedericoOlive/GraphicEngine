#pragma once
#include <glm/glm/vec3.hpp>
#include "GameObjects/Component.h"

class SAUCA_API BaseLight : public Component
{
protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	public:
	BaseLight() = default;
	~BaseLight() override;
	void Draw() override;
	void Update() override;
	void Input() override;
	void OnAsigned() override;
};