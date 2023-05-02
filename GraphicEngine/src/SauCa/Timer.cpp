#include "Timer.h"
#include <glfw3.h>

double Timer::deltaTime = 0;
double Timer::currentTime;
Timer::Timer()
{
	deltaTime = 0;
	currentTime = 0;
	prevTime = 0;
	timeDiff = 0;
	counterFrames = 0;
	resetNextFrame = false;
}

void Timer::Update()
{
	if(resetNextFrame)
	{
		resetNextFrame = false;
		prevTime = currentTime;
		counterFrames = 0;
	}
	double time = glfwGetTime();
	deltaTime = currentTime - time;
	currentTime = time;
	timeDiff = currentTime - prevTime;
	counterFrames++;

	if (IsEndCounter())
	{
		resetNextFrame = true;
	}
}

std::string Timer::GetTimeInfo() const
{
	std::string fps = std::to_string((1.0 / timeDiff) * counterFrames);
	std::string ms = std::to_string((timeDiff / counterFrames) * 1000);
	return (fps + "FPS / " + ms + "ms");
}
