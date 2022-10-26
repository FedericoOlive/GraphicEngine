#include "Time.h"

Time::Time()
{
}

void Time::Update()
{
	double time = glfwGetTime();
	deltaTime = time - currentTime;
	currentTime = time;	
}

double Time::DeltaTime()
{
	return deltaTime;
}

double Time::ElapsedTime()
{
	return currentTime;
}