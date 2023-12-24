#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h> // include glad to get the required OpenGL headers

#include <iostream>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Texture
{



private:
	int width, height, nrChanels;
	unsigned char* data;
	unsigned int textureData;
public:
	Texture(char* path);

	void use();
};

