#pragma once
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>
#include "camera.h"
class BlockRenderer
{
public:
	BlockRenderer(Shader& shader);
	~BlockRenderer();
	void DrawBlock(Texture diffuse, Texture specular, glm::vec3 position, Camera & cam);
	void setProjectionViewMatrix(const glm::mat4& matrix);
	void setLightPositions(const std::vector<glm::vec3>& positions);


private:
	Shader shader;
	unsigned int quadVAO;
	unsigned int VBO;// vertext buffer object holds the points
	glm::mat4 projectionViewMatrix;  // Projection-view matrix
	std::vector<glm::vec3> lightPositions;  // Light positions

	void initRenderData();

};

