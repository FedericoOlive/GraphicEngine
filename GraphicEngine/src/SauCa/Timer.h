#ifndef TIME_H
#define TIME_H
#include "Exports.h"
#include "glfw3.h"

class SAUCA_API Timer
{
private:
	double currentTime;
	static double deltaTime;

public:
	Timer();
	void Update();
	double static DeltaTime();
	double ElapsedTime();	
};
#endif