#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos) :pos(pos)
{
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            // Scale the coordinates to control the frequency of the Perlin noise
            float scaledX = (float)(x+(int)pos.x)  / 10.0f;
            float scaledZ = (float)(z+(int)pos.z) / 10.0f;
            // Generate Perlin noise for the scaled position
            float perlinValue = 0.5f * (1.0f + perlin(scaledX, scaledZ));

            // Linearly interpolate the height based on the scaled Perlin noise value
            float minHeight = 0.0f;
            float maxHeight = CHUNK_SIZE;  // Adjust this value for the maximum height

            float height = minHeight + (maxHeight - minHeight) * perlinValue;
            // Loop through the y-axis based on the calculated height
            for (int y = 0; y < height-1; ++y) {
                blocks[x][y][z] = DIRT;  // Set to STONE within the height range
            }
            blocks[x][(int)height-1][z] = GRASS;
            // Set the rest to AIR
            for (int y = height; y < CHUNK_SIZE; ++y) {
                blocks[x][y][z] = EMPTY;
            }
        }
    }
    initRenderData();
}

Chunk::~Chunk()
{
}
bool Chunk::isAir(int x,int y,int z) {
    bool temp = false;

    temp = (y > 0) ? (blocks[x][y - 1][z] == EMPTY) : true;
    // Top face
    temp |=  (y < CHUNK_SIZE - 1) ? (blocks[x][y + 1][z] == EMPTY) : true;
    // Front face
    temp |=  (z > 0) ? (blocks[x][y][z - 1] == EMPTY) : true;
    // Back face
    temp |=  (z < CHUNK_SIZE - 1) ? (blocks[x][y][z + 1] == EMPTY) : true;
    // Left face
    temp |=  (x > 0) ? (blocks[x - 1][y][z] == EMPTY) : true;
    // Right face
    temp |=  (x < CHUNK_SIZE - 1) ? (blocks[x + 1][y][z] == EMPTY) : true;

    return temp;
}

void Chunk::initRenderData()
{
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                if (blocks[x][y][z] != EMPTY) {
                    if (isAir(x, y, z)) {
                        unsigned int variable=0;
                        if ((y > 0) ? (blocks[x][y - 1][z] == EMPTY) : true) {
                            variable |= (1 << 0);  // Set bit 0
                        }
                        if ((y < CHUNK_SIZE - 1) ? (blocks[x][y + 1][z] == EMPTY) : true) {
                            variable |= (1 << 1);  // Set bit 1
                        }
                        if ((z > 0) ? (blocks[x][y][z - 1] == EMPTY) : true) {
                            variable |= (1 << 2);  // Set bit 2
                        }
                        if ((z < CHUNK_SIZE - 1) ? (blocks[x][y][z + 1] == EMPTY) : true) {
                            variable |= (1 << 3);  // Set bit 3
                        }
                        if ((x > 0) ? (blocks[x - 1][y][z] == EMPTY) : true) {
                            variable |= (1 << 4);  // Set bit 4
                        }
                        if ((x < CHUNK_SIZE - 1) ? (blocks[x + 1][y][z] == EMPTY) : true) {
                            variable |= (1 << 5);  // Set bit 5
                        }
                        if (variable > 0) {
                            variable |= (blocks[x][y][z] << 6);
                            visibleBlocks.push_back(glm::vec4(x, y, z, variable));
                        }

                    }
                }
            }
        }
    }
    
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * visibleBlocks.size(), &visibleBlocks[0], GL_STATIC_DRAW);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // Note: attribute location is 3
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1); // This makes sure that the VBO advances once per instance
}
