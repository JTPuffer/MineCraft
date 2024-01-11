#include "Chunk.h"

Chunk::Chunk(Shader& shader)
{
    this->shader = shader;
    lightPositions = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
    };
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            // Scale the coordinates to control the frequency of the Perlin noise
            float scaledX = (float)x / 20.0f;
            float scaledZ = (float)z / 20.0f;

            // Generate Perlin noise for the scaled position
            float perlinValue = 0.5f * (1.0f + perlin(scaledX, scaledZ));

            // Linearly interpolate the height based on the scaled Perlin noise value
            float minHeight = 0.0f;
            float maxHeight = CHUNK_SIZE;  // Adjust this value for the maximum height

            float height = minHeight + (maxHeight - minHeight) * perlinValue;

            // Loop through the y-axis based on the calculated height
            for (int y = 0; y < height; ++y) {
                blocks[x][y][z] = STONE;  // Set to STONE within the height range
            }
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
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &VBO);


}
void Chunk::setProjectionViewMatrix(const glm::mat4& matrix)
{
    projectionViewMatrix = matrix;
    shader.use();
    shader.setmat4("projection", projectionViewMatrix);
}
void Chunk::setLightPositions(const std::vector<glm::vec3>& positions) {
    lightPositions = positions;
}
// must change this to render chunk eventually
void Chunk::DrawChunk(Texture diffuse, Texture specular, glm::vec3 position, Camera& cam)
{
    shader.use();

    // point light 1
    shader.setarr3("pointLightPositions", lightPositions);

    // spotLight
    shader.setVec3("spotLight.position", cam.Position);
    shader.setVec3("spotLight.direction", cam.Front);

    glActiveTexture(GL_TEXTURE0);
    diffuse.use();
    glActiveTexture(GL_TEXTURE1);
    specular.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    shader.setmat4("model", model);
    shader.setmat4("view", cam.GetViewMatrix());

    glBindVertexArray(quadVAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, visibleBlocks.size());
    glBindVertexArray(0);

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
                        visibleBlocks.push_back(glm::vec4(x, y, z,1));
                    }
                }
            }
        }
    }
    
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * visibleBlocks.size(), &visibleBlocks[0], GL_STATIC_DRAW);


    // Assuming 'instanceVBO' is the VBO for instance positions
    

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

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &quadVAO);
    //drawing an object
    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Binds the Buffer and the vertext object together so they can share info
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// copys verticies into the buffer


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//tells open gl the format of the data given
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // Note: attribute location is 3
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1); // This makes sure that the VBO advances once per instance
}
