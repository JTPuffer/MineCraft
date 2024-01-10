#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

Shader ResourceManager::loadShader(std::string vShaderFile, std::string fShaderFile, std::string name)
{
	std::string vertexCode;
	std::string fragmentCode; // does colour

	std::ifstream vertFile(vShaderFile, std::ios::in);
	std::ifstream fragFile(fShaderFile, std::ios::in);

	if (!(vertFile.is_open() && fragFile.is_open())) {
		ErrorLogger::log("couldnt open files"+ vShaderFile + fShaderFile);
		return Shader();
	}
	try
	{
		std::stringstream vertexSteam, fragStream;

		vertexSteam << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();

		vertFile.close();
		fragFile.close();

		vertexCode = vertexSteam.str();
		fragmentCode = fragStream.str();
	}
	catch (std::ifstream::failure e)
	{
		ErrorLogger::log("failed to read files" + vShaderFile + fShaderFile);
	}


	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);
	Shaders[name] = shader;
    return shader;
}

Texture ResourceManager::loadTexture(const std::string file, std::string name)
{
	Texture texture;
	int width, height, nrChannels;
	unsigned char * data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);


	if (data) {
		texture.Generate(width, height, data, nrChannels);
	}
	else {
		ErrorLogger::log(" cant load data"+ file);
	}
	stbi_image_free(data);
	Textures[name] = texture;
    return texture;
}

 Texture & ResourceManager::GetTexture(const std::string name)
{
	return Textures[name];
}

 Shader& ResourceManager::GetShader(const std::string name)
{
	return Shaders[name];
}
