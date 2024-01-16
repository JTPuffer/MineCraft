#pragma once
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>
#include "camera.h"
#include "PerlinNoise.h"
#define CHUNK_SIZE 32
enum BlockType : uint8_t {
	EMPTY = 0,
	GRASS = 1,
	DIRT = 2,
	STONE = 3,
	// Add more block types as needed
};

class Chunk
{
public:
	Chunk(glm::vec3 pos);
	~Chunk();
	int count;
	int visible() { return visibleBlocks.size(); }
	unsigned int getVBO() { return VBO; }
	const glm::vec3 getPos() { return pos; }
private:
	BlockType blocks[CHUNK_SIZE][32][CHUNK_SIZE];
	unsigned int VBO;
	std::vector<glm::vec4> visibleBlocks;  // Light positions
	void initRenderData();
	bool isAir(int x, int y, int z);
	const glm::vec3 pos;

};

