#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

class SAUCA_API BoxCollider : public Collider
{
public:
	void Draw(Camera* camera) override;
	void Update() override;
	void Input() override;
	void OnAsigned() override;
	~BoxCollider() override;
};

#endif