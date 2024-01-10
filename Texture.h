#pragma once


#include <iostream>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ErrorLogger.h"

	class Texture
	{

	private:
		int width, height, nrChanels;
		unsigned int textureData;
	public:
		unsigned int Image_Format; // format of loaded image

		Texture() : nrChanels(0), width(0), height(0), Image_Format(GL_RGB) { glGenTextures(1, &textureData); };
		void Generate(unsigned int width, unsigned int height, unsigned char* data, unsigned int nrChannels);
		void use();
	};