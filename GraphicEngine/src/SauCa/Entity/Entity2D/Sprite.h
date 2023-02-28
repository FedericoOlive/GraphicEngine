#ifndef SPRITE_H
#define SPRITE_H

#include "Exports.h"
#include "Entity/Entity2D.h"
#include "Animation.h"
#include "Texture.h"
#include "Frame.h"
#include <vector>

class SAUCA_API Sprite : public Entity2D
{
protected:
	std::vector<Animation*> animations;
	Texture* texture;
	Frame frame;
	bool hasAnimation = false;
public:
	int heightTexture;
	int widthTexture;
	unsigned int UVBuffer;

	Sprite();
	Sprite(Texture* texture, Renderer* renderer);
	~Sprite();
	void DeleteTextureAsociate();
	void Draw(int anim = 0);
	void SetTexture(Texture* texture);
	void AddAnimation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs);
	void AddAnimation(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float durationInSecs, int frameCount);
	std::vector<Animation*> GetAnimations();
	void SetTextureCoordinates(glm::vec2 topRight, glm::vec2 bottomRight, glm::vec2 bottomLeft, glm::vec2 topLeft);
};

#endif