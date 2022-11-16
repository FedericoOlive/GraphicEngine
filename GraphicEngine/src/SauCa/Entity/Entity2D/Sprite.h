#ifndef SPRITE_H
#define SPRITE_H

#include "Exports.h"
#include "Animation.h"
#include "Texture.h"
#include "Entity/Entity2D.h"

class SAUCA_API Sprite : public Entity2D
{
private:
	Animation* animation;
public:
	Texture* texture;
	int heightTexture;
	int widthTexture;
	
	Sprite(Texture* texture, Renderer* renderer);
	~Sprite();
	void Draw();
	void SetTexture(Texture* texture);
	void AddAnimation(int countX, int countY);
};

#endif