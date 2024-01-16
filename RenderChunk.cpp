#include "RenderChunk.h"

RenderChunk::RenderChunk(Shader& shader, Texture& diffuse, Texture& specular)
{
    this->shader = shader;
    this->diffuse = diffuse;
    this->specular = specular;
    lightPositions = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
    };
    initRenderData();
}

RenderChunk::~RenderChunk()
{
}

void RenderChunk::setProjectionViewMatrix(const glm::mat4& matrix)
{
    projectionViewMatrix = matrix;
    shader.use();
    shader.setmat4("projection", projectionViewMatrix);
}

void RenderChunk::setLightPositions(const std::vector<glm::vec3>& positions)
{
    lightPositions = positions;
}

void RenderChunk::draw(Chunk& chunk,  Camera& cam)
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
    model = glm::translate(model, chunk.getPos());



    shader.setmat4("model", model);
    shader.setmat4("view", cam.GetViewMatrix());

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, chunk.getVBO());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//tells open gl the format of the data given
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glDrawArrays(GL_TRIANGLES, 0, chunk.count);
    glBindVertexArray(0);
}

void RenderChunk::initRenderData()
{
    glGenVertexArrays(1, &quadVAO);
    //drawing an object
    glBindVertexArray(quadVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//tells open gl the format of the data given
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

}
