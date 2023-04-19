#include "Tile.h"

Tile::Tile()
{
	id = 0;
	isWalkable = false;
	
}

Tile::Tile(int id, bool walkable, Renderer* render, const char* filePathImage, bool invertImage) : Sprite(texture, render)
{
	this->texture = nullptr;
	this->vertexData->indexes = nullptr;
	this->vertexData->vertices = nullptr;
	texture = nullptr;

	SetRenderer(render);
	this->id = id;
	isWalkable = walkable;
	texture = new Texture(filePathImage);
	SetTexture(texture);
}

Tile::~Tile()
{

}

bool Tile::IsWalkable()
{
	return isWalkable;
}

void Tile::Walkability(bool bWalkable)
{
	isWalkable = bWalkable;
}

unsigned int Tile::GetId()
{
	return id;
}

void Tile::SetId(unsigned int id)
{
	this->id = id;
}