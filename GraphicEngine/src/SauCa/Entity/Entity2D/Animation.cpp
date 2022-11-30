#include "Animation.h"

#include <string>
#include <sstream>

Animation::Animation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs)
{
	frameX *= frameWidth;
	frameY *= frameHeigth;
	length = durationInSecs;
	Frame frame;

	frame.coordinates[0].u = ((frameX) / textureWidth);
	frame.coordinates[0].v = ((frameY + frameHeigth) / textureHeigth);
	frame.coordinates[1].u = ((frameX) / textureWidth);
	frame.coordinates[1].v = (frameY / textureHeigth);
	frame.coordinates[2].u = (((frameX) + frameWidth) / textureWidth);
	frame.coordinates[2].v = (frameY / textureHeigth);
	frame.coordinates[3].u = (((frameX) + frameWidth) / textureWidth);
	frame.coordinates[3].v = ((frameY + frameHeigth) / textureHeigth);
	
	anim.push_back(frame);
}

Animation::Animation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs, int frameCount)
{
	frameX *= frameWidth;
	frameY *= frameHeigth;
	length = durationInSecs;

	for (int i = 0; i < frameCount; i++) {
		Frame frame;

		frame.coordinates[0].u = ((frameX + frameWidth * i) / textureWidth);
		frame.coordinates[0].v = ((frameY + frameHeigth) / textureHeigth);
		frame.coordinates[1].u = ((frameX + frameWidth * i) / textureWidth);
		frame.coordinates[1].v = (frameY / textureHeigth);
		frame.coordinates[2].u = (((frameX + frameWidth * i) + frameWidth) / textureWidth);
		frame.coordinates[2].v = (frameY / textureHeigth);
		frame.coordinates[3].u = (((frameX + frameWidth * i) + frameWidth) / textureWidth);
		frame.coordinates[3].v = ((frameY + frameHeigth) / textureHeigth);
		
		anim.push_back(frame);
	}
}

Animation::~Animation()
{
}

void Animation::Update()
{
	finished = false;
	currentTime += Timer::DeltaTime();

	while (currentTime > length) {
		currentTime -= length;
	}

	float frameLength = length / anim.size();
	currentFrame = static_cast<int>(currentTime / frameLength);
	if (currentFrame == anim.size()-1) {
		finished = true;
		currentTime = 0;
	}

}

bool Animation::IsFinished()
{
	return finished;
}



int Animation::CurrentFrame()
{
	return currentFrame;
}

vector<Frame>& Animation::GetFrames()
{
	return anim;
}
