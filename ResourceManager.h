#pragma once
#include "Shader.h"
#include "Texture.h"
#include "stb_image.h"

#include <map>
#include <string>
#include <iostream>

#include <glad/glad.h>

class ResourceManager
{
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture>	Textures;

	ResourceManager() {};
public:
	static Shader loadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
	static Texture loadTexture(const char* file, std::string name);
	static Texture GetTexture(std::string name);
	static Shader  GetShader(std::string name);
};

