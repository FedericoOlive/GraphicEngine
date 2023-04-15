#ifndef CUBE_H
#define CUBE_H
#include "../Entity3D.h"

class SAUCA_API Cube : public Entity3D
{
public:
	Cube(Renderer* renderer);
	~Cube() override;
	void Draw() override;
	void Update() override;
	void Input() override;
	void OnAsigned() override;
};
#endif