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


class Shader
{
public:
	unsigned int id;

	Shader(const char* vertexPath, const char * fragmentPath);

	void use();

	void setmat4(const char * uniformName, glm::mat4 matrix);

	void setVec3(const char* uniformName, glm::vec3 vec);
	void setFloat(const char* uniformName, float f);
};

