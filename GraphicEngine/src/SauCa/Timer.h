#ifndef TIME_H
#define TIME_H

#include <string>
#include "Exports.h"

class SAUCA_API Timer
{
private:
	static double deltaTime;
	double currentTime;
	double prevTime;
	double timeDiff;
	unsigned int counterFrames;
	bool resetNextFrame;
public:
	Timer();
	void Update();
	double static DeltaTime();
	double ElapsedTime();
	std::string GetTimeInfo() const;
	bool IsEndCounter() const { return (timeDiff > 1.0 / 30.0); }
};
#endif