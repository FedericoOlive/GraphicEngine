#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#include "Exports.h"
#include <iostream>

class SAUCA_API Texture
{
public:
	unsigned int texture;	
	Texture(std::string path);
};

#endif