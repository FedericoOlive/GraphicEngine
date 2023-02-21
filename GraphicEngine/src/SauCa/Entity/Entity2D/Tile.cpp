#include "Tile.h"

Tile::Tile() :Sprite(nullptr, nullptr)
{
	id = 0;
	isWalkable = false;
	this->renderer = nullptr;
	this->texture = nullptr;
	this->indices = nullptr;
	this->vertices = nullptr;
	texture = nullptr;
}

Tile::Tile(int id, bool walkable, Renderer* render, const char* filePathImage, bool invertImage):Sprite(texture,render)
{
	id = 0;
	isWalkable = false;
	this->renderer = nullptr;
	this->texture = nullptr;
	this->indices = nullptr;
	this->vertices = nullptr;
	texture = nullptr;
	
	this->renderer = render;
	id = id;
	isWalkable = walkable;
	texture = new Texture(filePathImage);
	SetTexture(texture);
}

Tile::~Tile()
{
	this->DeleteTextureAsociate();
}

bool Tile::IsWalkable()
{
	if (!isWalkable)
		return false;

	else
		return true;
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
	id = id;
}