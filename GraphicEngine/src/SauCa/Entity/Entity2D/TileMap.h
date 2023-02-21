#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class SAUCA_API TileMap
{
private:
	std::vector<Tile> tiles;
	std::vector<Tile**> tileMapGrid;

	unsigned int width;
	unsigned int height;

	float tileWidth;
	float tileHeight;

	Texture* texture;

	float imageWidth;
	float imageHeight;

	float convertedPosX;
	float convertedPosY;

	std::string imagePath;

	Renderer* currentRender;
	
public:
	TileMap(Renderer* render);
	~TileMap();

	const Tile& GetTile(unsigned int uiId);
	void SetTile(const Tile& rkTile);
	void SetMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId);

	void SetDimensions(float width, float heigth);
	void SetTileDimensions(float tileWidth, float tileHeigth);

	void SetTexture(Texture* rkTexture);
	void Draw();

	bool ImportTileMap(std::string filePath);
	bool CheckCollision(Entity2D& object);

	int GetWidth();
	int GetHeight();

	std::vector<Tile**> GetTilesGrid();
};

#endif