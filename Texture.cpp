#include "Texture.h"

Texture::Texture(char* path)
{
	data = stbi_load("container.jpg", &width, &height, &nrChanels, 0);

	if (data) {
		glGenTextures(1, &textureData);
		glBindTexture(GL_TEXTURE_2D, textureData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << " cant load data";
	}
	stbi_image_free(data);


}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureData);
}
