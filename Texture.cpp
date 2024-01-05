#include "Texture.h"

matts::Texture::Texture(const char* path)
{
	textureData = 0;
	data = stbi_load(path, &width, &height, &nrChanels, 0);

	if (data) {

		GLenum format;
		switch (nrChanels)
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


		glGenTextures(1, &textureData);
		glBindTexture(GL_TEXTURE_2D, textureData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << " cant load data";
	}
	stbi_image_free(data);


}

void matts::Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureData);
}
