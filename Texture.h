#pragma once

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
		unsigned int Image_Format; // format of loaded image

		Texture();
		void Generate(unsigned int width, unsigned int height, unsigned char* data, unsigned int nrChannels);
		void use();
	};