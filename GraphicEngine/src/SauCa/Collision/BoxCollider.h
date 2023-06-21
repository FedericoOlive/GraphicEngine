#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

class SAUCA_API BoxCollider : public Collider
{
public:
	~BoxCollider() override;
	void Draw(Camera* camera) override;
	void Update(double deltaTime) override;
	void Input() override;
	void OnAsigned() override;
};

#endif