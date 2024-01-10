#pragma once
#include "Shader.h"
#include "Texture.h"
#include "stb_image.h"

#include <map>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include "ErrorLogger.h"

class ResourceManager
{
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture>	Textures;

	ResourceManager() {};
public:
	static Shader loadShader(const std::string vShaderFile, const std::string fShaderFile, std::string name);
	static Texture loadTexture(const std::string file,const  std::string name);
	static  Texture& GetTexture(const std::string name);
	static  Shader&  GetShader(const std::string name);
};

