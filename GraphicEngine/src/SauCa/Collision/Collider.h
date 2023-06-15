#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObjects/Component.h"


class SAUCA_API Collider : public Component
{
public:
	enum class ColliderType
	{
		Box,
		Shere
	};

	Collider();
	~Collider() override;
	void Draw(Camera* camera) override;
	void Update() override;
	void Input() override;
	void OnAsigned() override;
};

#endif