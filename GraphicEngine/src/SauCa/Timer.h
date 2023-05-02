#ifndef TIME_H
#define TIME_H

#include <string>
#include "Exports.h"

class SAUCA_API Timer
{
private:
	static double deltaTime;
	static double currentTime;
	double prevTime;
	double timeDiff;
	unsigned int counterFrames;
	bool resetNextFrame;
public:
	Timer();
	void Update();
	static double DeltaTime() { return deltaTime; }
	static	double ElapsedTime() { return currentTime; }
	bool IsEndCounter() const { return (timeDiff > 1.0 / 30.0); }
	std::string GetTimeInfo() const;
};
#endif