#pragma once

#define SHADER_H
#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "ErrorLogger.h"

class Shader
{
public:
	unsigned int id;

	Shader() : id(0){};

	void use();
	void  Compile(const char* vertexSource, const char* fragmentSource);
	void setmat4(const char * uniformName, glm::mat4 matrix);

	void setVec2(const char* uniformName, glm::vec2 vec);
	void setVec3(const char* uniformName, glm::vec3 vec);
	void setFloat(const char* uniformName, float f);
	void setint(const char* uniformName, int i);
	void setarr3(const char* uniformName, std::vector<glm::vec3>& vec);
};

