#include "TileMap.h"
#include <map>
#include <windows.h>
#include "tinyxml2.h"

TileMap::TileMap(Renderer* render)
{
	renderer = render;
}

TileMap::~TileMap() {}

const Tile& TileMap::GetTile(unsigned int uiId) {
	Tile* NoTile = nullptr;

	for (int i = 0; i < tiles.size(); i++) {
		if (uiId == tiles[i].GetId()) {
			return tiles[i];
		}
	}

	return *NoTile;
}

void TileMap::SetMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId)
{
	tileMapGrid[layer][uiCol][uiRow] = GetTile(uiId);
}

void TileMap::SetTile(const Tile& rkTile)
{	
	tiles.push_back(rkTile);
}

void TileMap::SetTileDimensions(float _tileWidth, float _tileHeight)
{
	tileWidth = _tileWidth;
	tileHeight = _tileHeight;
}

void TileMap::SetDimensions(float _width, float _height)
{
	width = _width;
	height = _height;

	//creo la grilla bidimensional para guardar la posicion de cada Tile igual que en el editor
	Tile** tileMap;
	tileMap = new Tile * [height];
	for (int i = 0; i < height; i++) {
		tileMap[i] = new Tile[width];
	}
	tileMapGrid.push_back(tileMap);
}

void TileMap::SetTexture(Texture* rkTexture)
{
	texture = rkTexture;
}

void TileMap::Draw()
{
	//currentRender.setCurrentTexture(texture);

	float mapWidth = -(width * tileWidth) / 2.0f;
	float mapHeight = (height * tileHeight) / 2.0f;

	for (int i = 0; i < tileMapGrid.size(); i++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (tileMapGrid[i][y][x].GetId() != NULL)
				{
					glm::vec3 pos = glm::vec3(mapWidth + (tileWidth * x), mapHeight - (tileHeight * y), 0);
					//tileMapGrid[i][y][x].SetPosition(pos);
					tileMapGrid[i][y][x].Draw();
				}
			}
		}
	}

}

bool TileMap::ImportTileMap(string filePath, string resPath) {

	tinyxml2::XMLDocument doc; //guarda el documento
	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

	errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
	if (mapNode == nullptr)
		return false;
	SetDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
	SetTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles

	// Loading Tilset element
	tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset == NULL)
		return false;

	int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
	int columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
	int rows = tileCount / columns;

	//imagePath = "../res/assets/";																//
	//imagePath += pTileset->FirstChildElement("image")->Attribute("source");			// Loading Textures
	
	texture = new Texture(resPath,false); // textureImporter::loadTexture(imagePath.c_str(), true);
	renderer->BindTextures(texture->texture);
	renderer->SetSpriteAttributes();
	// Save the Tiles in the TileMap
	imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
	imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");
	float tileX = 0.0f, tileY = 0.0f;
	int _id = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Tile newTile;

			newTile.SetId(_id);
			newTile.SetTexture(texture);
			newTile.SetScale(glm::vec3(tileWidth, tileHeight, 1.0f));
			newTile.material = renderer->GetMaterialTexture();
			newTile.SetRenderer(renderer);
			
			newTile.SetTextureCoordinates(
				glm::vec2((tileX + tileWidth) / imageWidth, tileY / imageHeight),				 // Top Right
				glm::vec2((tileX + tileWidth) / imageWidth, (tileY + tileHeight) / imageHeight), // Bottom Right
				glm::vec2(tileX / imageWidth, (tileY + tileHeight) / imageHeight),				 // Bottom Left
				glm::vec2(tileX / imageWidth, tileY / imageHeight));							 // Top Left

			tileX += tileWidth;
			SetTile(newTile);
			_id++;
		}
		tileX = 0;
		tileY += tileHeight;
	}

	tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");

	while (pTile) {
		unsigned int id = pTile->IntAttribute("id");
		tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
		std::string propertyName = pProperty->Attribute("value");
		if (propertyName == "false")
			tiles[id].Walkability(false);
		else
			tiles[id].Walkability(true);

		pTile = pTile->NextSiblingElement("tile");
	}

	// Loading Layer element
	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer == NULL)
		return false;

	int layerCount = 0;
	while (pLayer) {
		// Loading Data element
		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
		if (pData == NULL)
			return false;

		if (layerCount > 0) {
			Tile** tileMap;
			tileMap = new Tile * [height];

			for (int i = 0; i < height; i++)
			{
				tileMap[i] = new Tile[width];
			}

			tileMapGrid.push_back(tileMap);
		}

		while (pData) {
			std::vector<int> tileGids;
			for (tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
				pTile != NULL;
				pTile = pTile->NextSiblingElement("tile"))
			{
				unsigned int gid = std::atoi(pTile->Attribute("gid")); // Tile's id is saved
				tileGids.push_back(gid);
			}

			int gid = 0;
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					if (tileGids[gid] != 0)
						SetMapTileId(layerCount, y, x, tileGids[gid]);
					gid++;
				}
			}

			pData = pData->NextSiblingElement("data");
		}
		layerCount++;
		pLayer = pLayer->NextSiblingElement("layer");
	}

	return true;
}

bool TileMap::CheckCollision(Entity2D& object)
{
	convertedPosX = object.GetPosition().x + (width / 2.0f) * tileWidth - pos.x;
	convertedPosY = object.GetPosition().y + (height / 2.0f) * tileHeight + pos.y;

	int left_tile = convertedPosX / tileWidth;
	int right_tile = (convertedPosX + object.GetScale().x) / tileWidth;

	int top_tile = (convertedPosY / tileHeight) * -1;
	int bottom_tile = ((convertedPosY - object.GetScale().y) / tileHeight) * -1; // Se resta porque el eje Y crece hacia arriba

	if (left_tile < 0)
		left_tile = 0;

	if (right_tile >= width)
		right_tile = width - 1;

	if (top_tile < 0)
		top_tile = 0;

	if (bottom_tile >= height)
		bottom_tile = height - 1;

	for (int i = left_tile; i <= right_tile; i++)
	{
		for (int j = top_tile; j <= bottom_tile; j++)
		{
			for (int k = 0; k < tileMapGrid.size(); k++)
			{
				//std::cout << "caminable " << "[" << k << "]" << "[" << j << "]" << "[" << i << "] : "<< tileMapGrid[k][j][i].isWalkable(); // true == 1  ; false == 0
				//cout << true << endl;
				if (!tileMapGrid[k][j][i].IsWalkable())
				{
					float overlapX = 0;
					float overlapY = 0;

					CollisionType colType = object.CheckCollision(tileMapGrid[k][j][i], overlapX, overlapY);
					
					if (colType != CollisionType::none)
					{
						//std::cout << "overlapx = " << overlapX << std::endl;
						//std::cout << "overlapy = " << overlapY << std::endl;
						cout << "Hay Colision!\n";
						object.ApplyCollisionRestrictions(colType, overlapX, overlapY, false);
						return true;
					}
				}
			}
		}

		//std::cout << std::endl;
	}

	return false;
}
int TileMap::GetWidth()
{
	return width;
}
int TileMap::GetHeight()
{
	return height;
}
std::vector<Tile**> TileMap::GetTilesGrid()
{
	return tileMapGrid;
}

void TileMap::SetSize(float size)
{
	float mapWidth = -(width * tileWidth / 2.f);
	float mapHeight = height * tileHeight / 2.f;

	for (int i = 0; i < tileMapGrid.size(); i++)
	{
		for (int y = 0; y < this->height; y++)
		{
			for (int x = 0; x < this->width; x++)
			{
				if (tileMapGrid[i][y][x].GetId() != NULL)
				{
					glm::vec3 pos = this->pos;
					pos.x += (mapWidth + (tileWidth * x)) * size;
					pos.y += (mapHeight - (tileHeight * y)) * size;
					tileMapGrid[i][y][x].SetPosition(pos.x, pos.y, pos.z);
					tileMapGrid[i][y][x].SetScale(tileWidth * size, tileHeight * size, 1.f);
				}
			}
		}
	}

	tileWidth *= size;
	tileHeight *= size;
}