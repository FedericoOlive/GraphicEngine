#ifndef TILE_H
#define TILE_H

#include "Entity/Entity2D/Sprite.h"

class SAUCA_API Tile : public Sprite
{
protected:
	unsigned int id;
	bool isWalkable;

public:
	Tile();
	Tile(int id, bool walkable, Renderer* render, const char* filePathImage, bool invertImage);
	~Tile();

	bool IsWalkable();
	void Walkability(bool bWalkable);

	unsigned int GetId();
	void SetId(unsigned int id);
};

#endif