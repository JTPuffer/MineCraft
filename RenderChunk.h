#pragma once
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>
#include "camera.h"
#include "Chunk.h"


class RenderChunk {
public:
    RenderChunk(Shader& shader,Texture& diffuse, Texture& specular );
    ~RenderChunk();

    void setProjectionViewMatrix(const glm::mat4& matrix);
    void setLightPositions(const std::vector<glm::vec3>& positions);
    void draw(Chunk& chunk,  Camera& cam);
        

private:
    Shader shader;
    unsigned int quadVAO;
    unsigned int VBO;

    Texture diffuse;
    Texture specular;

    glm::mat4 projectionViewMatrix;
    std::vector<glm::vec3> lightPositions;

    void initRenderData();
};