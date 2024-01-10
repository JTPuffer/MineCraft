#pragma once
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>
#include "camera.h"

#define CHUNK_SIZE 16
enum BlockType : uint8_t {
	EMPTY = 0,
	DIRT = 1,
	STONE = 2,
	// Add more block types as needed
};

class Chunk
{
public:
	Chunk(Shader& shader);
	~Chunk();
	void DrawChunk(Texture diffuse, Texture specular, glm::vec3 position, Camera& cam);
	void setChunk(BlockType* (blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]));
	void setProjectionViewMatrix(const glm::mat4& matrix);
	void setLightPositions(const std::vector<glm::vec3>& positions);

private:
	BlockType blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	Shader shader;
	unsigned int quadVAO;
	unsigned int VBO;// vertext buffer object holds the points
	unsigned int instanceVBO;
	glm::mat4 projectionViewMatrix;  // Projection-view matrix
	std::vector<glm::vec3> lightPositions;  // Light positions
	std::vector<glm::vec3> visibleBlocks;  // Light positions
	void initRenderData();
	bool isAir(int x, int y, int z);

};

