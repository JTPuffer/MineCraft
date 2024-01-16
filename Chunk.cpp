#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos) :pos(pos)
{
    count = 0;
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

    temp = (y > 0) ? (blocks[x][y - 1][z] == EMPTY) : false;
    // Top face
    temp |=  (y < CHUNK_SIZE - 1) ? (blocks[x][y + 1][z] == EMPTY) : false;
    // Front face
    temp |=  (z > 0) ? (blocks[x][y][z - 1] == EMPTY) : false;
    // Back face
    temp |=  (z < CHUNK_SIZE - 1) ? (blocks[x][y][z + 1] == EMPTY) : false;
    // Left face
    temp |=  (x > 0) ? (blocks[x - 1][y][z] == EMPTY) : false;
    // Right face
    temp |=  (x < CHUNK_SIZE - 1) ? (blocks[x + 1][y][z] == EMPTY) : false;

    return temp;
}
void translate(float x,float y,float z, int start,int end) {
    for (; start < end; start++) {

    }
}
void Chunk::initRenderData()
{
    float vertices[] = {
        // Back face changed text cords casue they be upside down in game
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,                    // Bottom-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,                   // bottom-right    
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,                   // top-right              
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,                   // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,                   // top-left
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,                   // bottom-left                
        // Front face
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,                    // bottom-left
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,                    // top-right
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,                    // bottom-right        
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,                    // top-right
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,                    // bottom-left
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,                    // top-left        
        // Left face
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,                    // top-right
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,                    // bottom-left
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,                    // top-left       
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,                    // bottom-left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,                    // top-right
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,                    // bottom-right
        // Right face
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,                   // top-left
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,                   // top-right      
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,                   // bottom-right          
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,                   // bottom-right
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,                   // bottom-left
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,                   // top-left
         // Bottom face          
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,                    // top-right
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,                    // bottom-left
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,                    // top-left        
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,                    // bottom-left
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,                    // top-right
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,                    // bottom-right
         // Top face
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,                   // top-left
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,                   // top-right
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,                   // bottom-right                 
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,                   // bottom-right
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,                   // bottom-left  
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f                   // top-left              
    };

    //CHANGE THIS TO RIGHT SHIFT

    const int sizeOfFace = sizeof(vertices) / (6 * sizeof(float));
    const int backFace = sizeOfFace * 0;
    const int frontFace = sizeOfFace * 1;
    const int leftFace = sizeOfFace * 2;
    const int rightFace = sizeOfFace * 3;
    const int bottomFace = sizeOfFace * 4;
    const int topFace = sizeOfFace * 5;

    std::vector<float> vert;
    float blockSize = 2/CHUNK_SIZE;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int y = 0; y < CHUNK_SIZE; ++y) {
                if (blocks[x][y][z] != EMPTY) {
                    //bottom face
                    if ((y > 0) ? (blocks[x][y - 1][z] == EMPTY) : false) {
                        vert.insert(vert.end(), vertices + bottomFace, vertices + bottomFace + sizeOfFace);
                       // vert.push_back(blocks[x][y][z]);
                        count += 6;
                    }
                    // Top face
                    if ((y < CHUNK_SIZE - 1) ? (blocks[x][y + 1][z] == EMPTY) : false) {
                        vert.insert(vert.end(), vertices + topFace, vertices + topFace + sizeOfFace);
                        //vert.push_back(blocks[x][y][z]);
                        count += 6;
                    }
                    // Front face
                    if ((z > 0) ? (blocks[x][y][z - 1] == EMPTY) : false) {
                        vert.insert(vert.end(), vertices + frontFace, vertices + frontFace + sizeOfFace);
                        //vert.push_back(blocks[x][y][z]);
                        count += 6;
                    }
                    // Back face
                    if ((z < CHUNK_SIZE - 1) ? (blocks[x][y][z + 1] == EMPTY) : false) {
                        vert.insert(vert.end(), vertices + backFace, vertices + backFace + sizeOfFace);
                        //vert.push_back(blocks[x][y][z]);
                        count += 6;
                    }
                    // Left face
                    if ((x > 0) ? (blocks[x - 1][y][z] == EMPTY) : false) {
                        vert.insert(vert.end(), vertices + leftFace, vertices + leftFace + sizeOfFace);
                        //vert.push_back(blocks[x][y][z]);
                        count += 6;
                    }
                    // Right face
                    if ((x < CHUNK_SIZE - 1) ? (blocks[x + 1][y][z] == EMPTY) : false) {
                        vert.insert(vert.end(), vertices + rightFace, vertices + rightFace + sizeOfFace);
                        //vert.push_back(blocks[x][y][z]);
                        count += 6;
                    }
                }
            }
        }
        
    }   

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Binds the Buffer and the vertext object together so they can share info
    glBufferData(GL_ARRAY_BUFFER, vert.size() *sizeof(float), &vert[0], GL_STATIC_DRAW);// copys verticies into the buffer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//tells open gl the format of the data given
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
    //glEnableVertexAttribArray(3);

}
//    for (int i = 0; i < sizeof(vertices)/sizeof(float); ++i) {
//vertices[i] /= CHUNK_SIZE;
//    }
