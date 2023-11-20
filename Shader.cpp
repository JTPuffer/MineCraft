#include "Shader.h"

Shader::Shader(const char* vertexPath, const char * fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode; // does colour

	std::ifstream vertFile(vertexPath, std::ios::in);
	std::ifstream fragFile(fragmentPath, std::ios::in);

	if (!(vertFile.is_open() && fragFile.is_open())) {
		std::cout << "couldnt open files";
		return ;
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
		std::cout << "failed to read files";
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int fragmentShader;
	int success;
	char infoLog[512];
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);//ig puts it all in the right place
	glCompileShader(fragmentShader);// starts compiling
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return ;
	}
	unsigned int vertextShader;
	vertextShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertextShader, 1, &vShaderCode, NULL);//ig puts it all in the right place
	glCompileShader(vertextShader);// starts compiling
	glGetShaderiv(vertextShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertextShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return;
	}

	id = glCreateProgram();
	glAttachShader(id, vertextShader);
	glAttachShader(id, fragmentShader);

	glDeleteShader(vertextShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(id);// links the program to the opengl instance so it can be used

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKINGERROR\n" << infoLog << std::endl;
	}
	glDeleteShader(vertextShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(id);
}
