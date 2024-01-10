#include "Shader.h"

void Shader::Compile(const char* vertexSource, const char* fragmentSource)
{
	unsigned int fragmentShader;
	int success;
	char infoLog[512];
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);//ig puts it all in the right place
	glCompileShader(fragmentShader);// starts compiling
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		ErrorLogger::log("ERROR::SHADER::VERTEX::COMPILATION_FAILED " + std::string(infoLog, strlen(infoLog)));
		return;
	}
	unsigned int vertextShader;
	vertextShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertextShader, 1, &vertexSource, NULL);//ig puts it all in the right place
	glCompileShader(vertextShader);// starts compiling
	glGetShaderiv(vertextShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertextShader, 512, NULL, infoLog);
		ErrorLogger::log("ERROR::SHADER::VERTEX::COMPILATION_FAILED" + std::string(infoLog, strlen(infoLog)));
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
		ErrorLogger::log("ERROR::SHADER::LINKINGERROR" + std::string(infoLog, strlen(infoLog)));
	}
}


void Shader::use()
{
	glUseProgram(id);
}

void Shader::setmat4(const char* uniformName, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id, uniformName)
		, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const char* uniformName, glm::vec3 vec)
{
	glUniform3fv(glGetUniformLocation(id, uniformName),1,  glm::value_ptr(vec));
}

void Shader::setFloat(const char* uniformName, float f)
{
	glUniform1fv(glGetUniformLocation(id, uniformName), 1, &f);
}

void Shader::setint(const char* uniformName, int i)
{
	glUniform1iv(glGetUniformLocation(id, uniformName),1, &i);

}

void Shader::setarr3(const char* uniformName,std::vector<glm::vec3>& vec)
{
	// Set light positions as a uniform array
	glUniform3fv(glGetUniformLocation(id, uniformName), vec.size(), &vec[0][0]);

}

