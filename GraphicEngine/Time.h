#ifndef TIME_H
#define TIME_H
#include "Exports.h"
#include "glfw3.h"

class SAUCA_API Time
{
private:
	double currentTime;
	double deltaTime;

public:
	Time();
	void Update();
	double DeltaTime();
	double ElapsedTime();	
};
#endif