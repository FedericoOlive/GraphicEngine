#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/vec3.hpp>
#include "GameObjects/Component.h"

class SAUCA_API Collider : public Component
{
public:
	enum class ColliderType
	{
		Box,
		Shere
	};

	float lineWidth;
	glm::vec3 color;
	bool isCollision;
	
	Collider();
	~Collider() override;
	void Draw(Camera* camera) override;
	void Update(double deltaTime) override;
	void Input() override;
	void OnAsigned() override;
};

#endif