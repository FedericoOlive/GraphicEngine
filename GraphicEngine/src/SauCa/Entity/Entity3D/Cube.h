#pragma once
#include "../Entity3D.h"
class Cube : public Entity3D
{
public:
	Cube(Renderer* renderer);
	~Cube() override;
	void Draw() override;
	void Update() override;
	void Input() override;
	void OnAsigned() override;
};