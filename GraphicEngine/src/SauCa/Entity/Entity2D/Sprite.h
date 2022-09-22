#ifndef SPRITE_H
#define SPRITE_H

#include "Exports.h"
#include "Animation.h"
#include "Texture.h"
#include "Entity/Entity2D.h"

class SAUCA_API Sprite : public Entity2D
{
public:
	Animation* animation;
	unsigned int texture;
	
	Sprite(Texture* texture, Renderer* renderer);
	~Sprite();
	void Draw();
};

#endif