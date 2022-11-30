#ifndef ANIMATION_H
#define ANIMATION_H

#include "Exports.h"
#include "Texture.h"
#include "Quad.h"
#include "Timer.h"
#include "Frame.h"

#include <vector>

using namespace std;

class SAUCA_API Animation
{
public:
	Animation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs);
	Animation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs, int frameCount);
	~Animation();
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