#include "Timer.h"

double Timer::deltaTime = 0;

Timer::Timer()
{
	deltaTime = 0;
	currentTime = 0;
}

void Timer::Update()
{
	double timeClock = glfwGetTime();
	deltaTime = timeClock - currentTime;
	currentTime = timeClock;
}

double Timer::DeltaTime()
{
	return deltaTime;
}


double Timer::ElapsedTime()
{
	return currentTime;
}