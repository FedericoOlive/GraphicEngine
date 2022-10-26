#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#include "Exports.h"
#include <iostream>

class SAUCA_API Texture
{
private:
	void BindTexture();
	void SetTextureWrapping(int textureWrapping);
	void SetTextureFiltering(int textureFiltering);
	void LoadImage(std::string path);
	Texture(std::string path, int textureWrapping, int textureFiltering);
	
public:
	int width;
	int height;
	unsigned int texture;
	Texture(std::string path);
};

#endif