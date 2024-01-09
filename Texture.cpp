#include "Texture.h"

Texture::Texture() : width(0), height(0), Image_Format(GL_RGB) { glGenTextures(1, &textureData); }


void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data,unsigned int nrChannels)
{
	this->width = width;
	this->height = height;
	GLenum format;
	switch (nrChannels)
	{
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		break;
	}
	glBindTexture(GL_TEXTURE_2D, textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureData);
}
