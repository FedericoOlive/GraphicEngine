#ifndef SPRITE_H
#define SPRITE_H

#include "Exports.h"
#include "Animation.h"
#include "Texture.h"
#include "Frame.h"
#include "Entity/Entity2D.h"
#include <vector>

class SAUCA_API Sprite : public Entity2D
{
private:
	std::vector<Animation*> animations;
	Texture* texture;
	Frame frame;
	bool hasAnimation;
public:
	int heightTexture;
	int widthTexture;
	unsigned int UVBuffer;
		
	Sprite(Texture* texture, Renderer* renderer);
	~Sprite();
	void DeleteTextureAsociate();
	void Draw(int anim = 0);
	void SetTexture(Texture* texture);
	void AddAnimation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs);
	void AddAnimation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs, int frameCount);
};

#endif