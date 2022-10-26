#include <glew.h>
#include <string>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi.h"

void Texture::BindTexture()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::SetTextureWrapping(int textureWrapping)
{
    switch (textureWrapping)
    {
    case 0:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        break;
    case 1:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        break;
    case 2:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
    case 3:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        break;
    default:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
    }
}

void Texture::SetTextureFiltering(int textureFiltering)
{
    switch (textureFiltering)
    {
    case 0:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case 1:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    default:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    }
}

void Texture::LoadImage(std::string path)
{
    int  nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        int channelType = GL_RGB;
        switch (nrChannels)
        {
        case 1:
            channelType = GL_R;
            break;
        case 2:
            channelType = GL_RG;
            break;
        case 3:
            channelType = GL_RGB;
            break;
        case 4:
            channelType = GL_RGBA;
            break;
        default:
            break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, channelType, width, height, 0, channelType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

Texture::Texture(std::string path)
{
    BindTexture();
    SetTextureWrapping(99);
    SetTextureFiltering(99);
    LoadImage(path);
}

/// <param name="textureWrapping">0: Repeat, 1: Mirrored Repeat, 2: Clamp To Edge, 3: Clamp To Border</param>
/// <param name="textureFiltering">0: Linear, 1: Nearest</param>
Texture::Texture(std::string path, int textureWrapping, int textureFiltering)
{
    BindTexture();
    SetTextureWrapping(textureWrapping);
    SetTextureFiltering(textureFiltering);
    LoadImage(path);
}