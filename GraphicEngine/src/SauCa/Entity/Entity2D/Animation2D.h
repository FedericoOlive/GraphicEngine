#ifndef ANIMATION2D_H
#define ANIMATION2D_H

#include "Frame.h"

#include <vector>

using namespace std;

class SAUCA_API Animation2D
{
public:
	Animation2D(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs);
	Animation2D(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs, int frameCount);
	~Animation2D();
	void Update();
	bool IsFinished();
	int CurrentFrame();

	vector<Frame>& GetFrames();
private:
	float currentFrame;
	float currentTime;
	float length;
	bool finished;

	vector<Frame> anim;	
};

#endif